/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:45:00 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/02 20:33:32 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
