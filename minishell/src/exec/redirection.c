/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:01:11 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/21 15:33:47 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	fill_here_doc(int *fd, t_redir **node, t_env **env)
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
			exit (0);
		}
		if ((*node)->target->sub_token->quote == NONE)
			line = app_expend(line, (*env), 0);
		if (!line)
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
}

int	prepare_here_doc(t_redir *node, t_env *env)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		error_pipe();
	pid = fork();
	if (pid == -1)
		error_pid_pipe();
	if (pid == 0)
	{
		g_signal = 0;
		init_signals();
		close(fd[0]);
		fill_here_doc(fd, &node, &env);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	node->fd = fd[0];
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

void	run_through_here_doc(t_ast *ast, t_env *env)
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
						prepare_here_doc(redir, env);
					redir = redir->next;
				}
			}
		}
		if (current->left)
			run_through_here_doc(current->left, env);
		if (current->right)
			run_through_here_doc(current->right, env);
	}
}

void	redirection(t_ast *node)
{
	int		fd;
	t_redir	*current;	

	current = node->redirs;
	if (!current)
		return ;
	current->stdin = dup(0);
	current->stdout = dup(1);
	while (current)
	{
		if (current->type == 1)
			redir_stdin(fd, current);
		if (current->type == 2)
			redir_stdout_trunc(fd, current);
		if (current->type == 3)
		{
			fd = current->fd;
			dup2(fd, 0);
			close(fd);
		}
		if (current->type == 4)
			redir_stdout_append(fd, current);
		current = current->next;
	}
}

void	restore_redirection(t_ast *node)
{
	t_redir	*current;	

	current = node->redirs;
	if (!current)
		return ;
	while (current)
	{
		if (current->type == 1 || current->type == 3)
		{
			dup2(current->stdin, 0);
			close(current->stdin);
		}
		if (current->type == 2 || current->type == 4)
		{
			dup2(current->stdout, 1);
			close(current->stdout);
		}
		current = current->next;
	}
}
