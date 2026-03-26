/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:01:11 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/26 21:09:16 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	free_all_in_child(t_global *global)
{
	int	error;

	if (*(global->what_free) == 1)
		global->true_head = global->head;
	ft_miniclear(&(global->true_head));
	free_parser(global->ast);
	if (global->env)
		free_env(global->env);
	error = *(global->error_code);
	free(global->error_code);
	free(global->what_free);
	free(global);
	return (error);
}

int	free_all_pipe_subshell(t_global *global)
{
	int	error;

	if (*(global->what_free) == 1)
		global->true_head = global->head;
	ft_miniclear(&(global->true_head));
	free_parser(global->ast);
	if (global->env)
		free_env(global->env);
	error = *(global->error_code);
	free(global->error_code);
	free(global->what_free);
	free(global);
	return (error);
}

void	fill_here_doc(int *fd, t_redir **node, t_global *global)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if ((ft_strncmp(line, (*node)->target->sub_token->var,
					(ft_strlen((*node)->target->sub_token->var) + 1)) == 0))
		{
			free(line);
			close(fd[1]);
			free_all_in_child(global);
			exit (0);
		}
		if ((*node)->target->sub_token->quote == NONE)
			line = app_expend(line, global, 0);
		if (!line)
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
}

int	prepare_here_doc(t_redir *node, t_global *global)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	status = 0;
	if (pipe(fd) == -1)
		error_pipe();
	pid = fork();
	if (pid == -1)
		error_pid();
	if (pid == 0)
	{
		g_signal = 0;
		init_signals();
		close(fd[0]);
		fill_here_doc(fd, &node, global);
		free_all_in_child(global);
		exit(1);
	}
	close(fd[1]);
	printf("%d\n", status);
	waitpid(pid, &status, 0);
	if (status > 0)
		close(fd[0]);
	node->fd = fd[0];
	//close(fd[0]);
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
						prepare_here_doc(redir, global);
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

int	redirection(t_ast *node, t_global *global)
{
	int		fd;
	t_redir	*current;
	int		code;

	code = 0;
	current = node->redirs;
	if (!current)
		return (0);
	current->stdin = dup(0);
	current->stdout = dup(1);
	while (current)
	{
		if (current->type == 1)
			redir_stdin(current, global, &code);
		if (code != 0)
		return (1);
		if (current->type == 2)
			redir_stdout_trunc(current, global, &code);
		if (code != 0)
		return (1);
		if (current->type == 3)
		{
			fd = current->fd;
			dup2(fd, 0); 
			close(fd);
		}
		if (code != 0)
		return (1);
		if (current->type == 4)
			redir_stdout_append(current, global, &code);
		current = current->next;
	}
	if (code != 0)
		return (1);
	return (0);
}

void	restore_redirection(t_ast *node)
{
	t_redir	*current;	

	current = node->redirs;
	if (!current)
		return ;
	while (current)
	{
		if (current->stdin != -1)
		{
			dup2(current->stdin, 0);
			close(current->stdin);
		}
		if (current->stdout != -1)
		{
			dup2(current->stdout, 1);
			close(current->stdout);
		}
		if (current->fd != 0)
			close(current->fd);
		current = current->next;
	}
}
