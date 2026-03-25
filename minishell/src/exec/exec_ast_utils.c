/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:22:04 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/25 13:50:54 by ibrouin-         ###   ########.fr       */
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
		if (current->stdin != -1)
			close(current->stdin);
		if (current->stdout != -1)
			close(current->stdout);
		current = current->next;
	}
}

void	child_cmd(t_ast **ast, char **path, t_global *global)
{
	(void)global;
	init_child_signals();
	redirection(*ast, global);
	close_saved_fd(*ast);
	if (*(global->error_code) == 127)
	{
		free(*path);
		ft_miniclear(&(global->head));
		free_parser(global->ast);
		exit (1);
	}
	execve(*path, (*ast)->cmd2, global->env->table);
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
	exit(*global->error_code);
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
	exit(*global->error_code);
}
