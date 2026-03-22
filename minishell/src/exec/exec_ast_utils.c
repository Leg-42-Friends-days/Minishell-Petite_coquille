/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:22:04 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/22 17:30:01 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	close_saved_fd(t_ast *ast)
{
	t_redir	*current;

	if (!ast)
		return ;
	current = ast->redirs;
	if (!current)
		return ;
	while (current)
	{
		if (ast->redirs->stdin != -1)
			close(ast->redirs->stdin);
		if (ast->redirs->stdout != -1)
			close(ast->redirs->stdout);
		current = current->next;
	}
}

void	child_cmd(t_ast **ast, char **path, t_global *global)
{
	(void)global;
	init_child_signals();
	redirection(*ast);
	close_saved_fd(*ast);
	execve(*path, (*ast)->cmd2, NULL);
	free(*path);
	ft_miniclear(&(global->head));
	free_parser(global->ast);
	perror("minishell");
	exit (127);
}

void	pipe_first_child(t_ast **ast, int *fd, t_env **env, t_global *global)
{
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	execution_2((*ast)->left, *env, global->error_code, global);
	close_saved_fd(*ast);
	ft_miniclear(&(global->head));
	free_parser(global->ast);
	exit(0);
}

void	pipe_second_child(t_ast **ast, int *fd, t_env **env, t_global *global)
{
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	execution_2((*ast)->right, *env, global->error_code, global);
	close_saved_fd(*ast);
	ft_miniclear(&(global->head));
	free_parser(global->ast);
	exit(0);
}
