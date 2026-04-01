/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:45:00 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/01 22:55:38 by ibrouin-         ###   ########.fr       */
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
    write(1, "\n", 1);
    g_signal = 130;
    close(0);
}

int	empty_line(char *line, int *fd)
{
	if (!line)
	{
		close(fd[1]);
		return(1);
	}
	return (0);
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
		if (g_signal == 130)
		{
			close(fd[1]);
			free_all_in_child(global, NULL);
			g_signal = 0;
			exit(1);			
		}
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if ((ft_strncmp(line, (*node)->target->sub_token->var,
					(ft_strlen((*node)->target->sub_token->var) + 1)) == 0))
			if_limiter(line, global, fd);
		if ((*node)->target->sub_token->quote == NONE)
			line = app_expend(line, global, 0);
		if (!line)
		{
			close(fd[1]);
			break ;
		}
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
	fill_here_doc(fd, &node, global);
	free_all_in_child(global, NULL);
	exit(1);
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
	{
		child_here_doc(fd, node, global);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (status > 0)
		close(fd[0]);
	close_previous_heredocs(node);
	node->fd = fd[0];
	init_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

void	run_through_here_doc(t_ast *ast, t_env *env, t_global *global)
{
	t_ast	*current;
	t_redir	*redir;

	current = ast;
	if (ast != NULL)
	{
		if (current->type == AST_CMD || current->type == AST_SUBSHELL)
		{
			redir = current->redirs;
			if (redir)
			{
				while (redir)
				{
					if (redir->type == HEREDOC)
						if (prepare_here_doc(redir, global) == 1)
							global->here_doc_error = 1;
					redir = redir->next;
				}
			}
		}
		if (current->left)
			run_through_here_doc(current->left, env, global);
		if (current->right)
			run_through_here_doc(current->right, env, global);
	}
}
