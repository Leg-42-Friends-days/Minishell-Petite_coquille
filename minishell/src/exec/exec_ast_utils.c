/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:22:04 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/21 15:32:57 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	child_cmd(t_ast **ast, char **path)
{
	init_child_signals();
	redirection(*ast);
	execve(*path, (*ast)->cmd2, NULL);
	perror("minishell");
	exit (127);
}

void	pipe_first_child(t_ast **ast, int *fd, t_env **env, t_global *global)
{
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	execution_2((*ast)->left, *env, global->error_code, global);
	exit(0);
}

void	pipe_second_child(t_ast **ast, int *fd, t_env **env, t_global *global)
{
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	execution_2((*ast)->right, *env, global->error_code, global);
	exit(0);
}
