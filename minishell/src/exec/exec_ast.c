/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:21:53 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/25 13:51:12 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
	{
		perror("minishell");
		free(path);
		return (127);
	}
	if (S_ISDIR(st.st_mode))
	{
		write(1, "minishell: ", 11);
		write(1, path, ft_strlen(path));
		write(1, ": Is a directory\n", 17);
		free(path);
		return (126);
	}
	return (0);
}

int	exec_cmd(t_ast *ast, t_env *env, t_global *global)
{
	char	*path;
	pid_t	pid;
	int		status;

	g_signal = 1;
	status = 0;
	path = init_path(&ast, env);
	if (!path)
		return (127);
	status = is_directory(path);
	if (status != 0)
		return (status);
	pid = fork();
	if (pid == -1)
		error_pid(&path);
	if (pid == 0)
		child_cmd(&ast, &path, global);
	free(path);
	waitpid(pid, &status, 0);
	signal(SIGINT, handler);
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
		error_pid_pipe();
	if (pid[0] == 0)
		pipe_first_child(&ast, fd, &env, global);
	pid[1] = fork();
	if (pid[1] == -1)
		error_pid_pipe();
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
	*(g->what_free) = 1;
	pid = fork();
	if (pid == -1)
		error_pid_pipe();
	if (pid == 0)
	{
		expand_function(ast, g);
		redirection(ast, g);
		close_saved_fd(ast);
		execution_2(ast->left, env, error_code, g);
		ft_miniclear(&(g->true_head));
		free_parser(g->ast);
		exit (*error_code);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*error_code = (WEXITSTATUS(status));
	return ;
}
