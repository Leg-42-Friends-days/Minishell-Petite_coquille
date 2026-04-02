/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:45:00 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/02 19:23:24 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	close_previous_heredocs(t_redir *node)
{
	t_redir	*current;

	if (!node)
		return ;
	current = node;
	while (current)
	{
		if (current->type == HEREDOC && current->fd != -1)
		{
			close(current->fd);
			current->fd = -1;
		}
		current = current->next;
	}
}

void	hand(int signum)
{
	(void)signum;
	g_signal = 130;
	write(1, "\n", 1);
	close(0);
}

int	empty_line(char *line, int *fd)
{
	if (!line)
	{
		close(fd[1]);
		return (1);
	}
	return (0);
}

void handle_sigquit(int sig)
{
    (void)sig;
    write(1, "\b\b  \b\b", 6);
}

void	fill_here_doc(int *fd, t_redir **node, t_global *global)
{
	char	*line;

	close_saved_fd(global->ast);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (empty_line(line, fd))
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if ((ft_strncmp(line, (*node)->target->sub_token->var,
					(ft_strlen((*node)->target->sub_token->var) + 1)) == 0))
			if_limiter(line, global, fd);
		if ((*node)->target->sub_token->quote == NONE)
			line = app_expend(line, global, 0);
		if (empty_line(line, fd))
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
}

void	child_here_doc(int *fd, t_redir *node, t_global *global)
{
	join_limiter(node);
	g_signal = 0;
	close(fd[0]);
	signal(SIGINT, hand);
	signal(SIGQUIT, handle_sigquit);
	fill_here_doc(fd, &node, global);
	get_next_line(-1);
	close(fd[1]);
	free_all_in_child(global, NULL);
	if (g_signal == 130)
		exit(130);
	exit(0);
}

int	heredoc_code_status(int *fd, t_redir *node, int status)
{
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) != 0)
		{
			close(fd[0]);
			node->fd = -1;
			return (WEXITSTATUS(status));
		}
		node->fd = fd[0];
		return (0);
	}
	close(fd[0]);
	node->fd = -1;
	return (0);
}

int	prepare_here_doc(t_redir *node, t_global *global)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	status = 0;
	init_child_signal_ig();
	if (pipe(fd) == -1)
		error_pipe();
	pid = fork();
	if (pid == -1)
		error_pid();
	if (pid == 0)
		child_here_doc(fd, node, global);
	close(fd[1]);
	waitpid(pid, &status, 0);
	close_previous_heredocs(node);
	init_signals();
	return (heredoc_code_status(fd, node, status));
}

int	handle_heredocs(t_ast *current, t_global *global)
{
	t_redir	*redir;
	int		error;

	error = 0;
	redir = current->redirs;
	if (!redir)
		return (0);
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			error = prepare_here_doc(redir, global);
			if (error != 0)
			{
				global->here_doc_error = 1;
				global->error_code = error;
				return (1);
			}
		}
		redir = redir->next;
	}
	return (0);
}

bool	is_heredoc_node(t_ast *current)
{
	if (current->type == AST_CMD || current->type == AST_SUBSHELL)
		return (true);
	return (false);
}

void	run_through_here_doc(t_ast *ast, t_env *env, t_global *global)
{
	if (!ast)
		return ;
	if (is_heredoc_node(ast) == true)
		if (handle_heredocs(ast, global))
			return ;
	if (ast->left)
		run_through_here_doc(ast->left, env, global);
	if (ast->right)
		run_through_here_doc(ast->right, env, global);
}
