/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:21:53 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/02 20:28:51 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	exec_cmd(t_ast *ast, t_env *env, t_global *global)
{
	pid_t	pid;
	int		status;
	int		sig;

	(void)env;
	g_signal = 1;
	status = 0;
	pid = fork();
	if (pid == -1)
		error_pid();
	if (pid == 0)
		child_cmd(&ast, global);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		return (signal_value(sig));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

void	exec_pipe(t_ast *ast, t_env *env, int *error_code, t_global *global)
{
	int		fd[2];
	pid_t	pid[2];
	int		status;

	g_signal = 1;
	if (pipe(fd) == -1)
		error_pipe();
	pid[0] = fork();
	if (pid[0] == -1)
		error_pid();
	if (pid[0] == 0)
		pipe_first_child(&ast, fd, &env, global);
	pid[1] = fork();
	if (pid[1] == -1)
		error_pid();
	if (pid[1] == 0)
		pipe_second_child(&ast, fd, &env, global);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);
	if (WIFEXITED(status))
		*error_code = (WEXITSTATUS(status));
}

void	exec_and(t_ast *ast, t_env *env, int *error_code, t_global *global)
{
	g_signal = 1;
	execution_2(ast->left, env, error_code, global);
	if (*error_code == 0)
		execution_2(ast->right, env, error_code, global);
}

void	exec_or(t_ast *ast, t_env *env, int *error_code, t_global *global)
{
	g_signal = 1;
	execution_2(ast->left, env, error_code, global);
	if (*error_code != 0)
		execution_2(ast->right, env, error_code, global);
}

void	exec_subshell(t_ast *ast, t_env *env, int *error_code, t_global *g)
{
	pid_t	pid;
	int		status;

	g_signal = 1;
	status = 0;
	pid = fork();
	if (pid == -1)
		error_pid();
	if (pid == 0)
	{
		expand_function(ast, g);
		redirection(ast, g);
		close_saved_fd(g->ast);
		execution_2(ast->left, env, error_code, g);
		free_subshell(g);
	}
	waitpid(pid, &status, 0);
	close_saved_fd(g->ast);
	if (WIFEXITED(status))
		*error_code = (WEXITSTATUS(status));
	return ;
}
