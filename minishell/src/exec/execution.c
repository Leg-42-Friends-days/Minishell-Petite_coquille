/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:28:07 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/20 17:03:41 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_bult_in(char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "exit", 5) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (1);
	return (0);
}

int	exec_bult_in(char **cmd, t_env *env, int *error_code)
{
	int	exit_status;

	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		exit_status = ft_echo(cmd, env);
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		exit_status = ft_cd(cmd, env);
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		exit_status = ft_pwd(cmd, env);
	if (ft_strncmp(cmd[0], "exit", 5) == 0)
		exit_status = ft_exit(cmd, env, error_code);
	if (ft_strncmp(cmd[0], "export", 7) == 0)
		exit_status = function_export(env, cmd);
	if (ft_strncmp(cmd[0], "env", 4) == 0)
		exit_status = affichage_env(env);
	if (ft_strncmp(cmd[0], "unset", 6) == 0)
		exit_status = function_unset(env, cmd);
	return (exit_status);
}

void	print_tab(char **tabl)
{
	int	i;

	i = 0;
	while (tabl[i] != NULL)
	{
		printf("%s\n", tabl[i]);
		i++;
	}
}

void	execution_2(t_ast *ast, t_env *env, int *error_code, t_global *global)
{
	if (ast != NULL)
	{
		if (ast->type == AST_CMD)
		{
			expand_function(global);
			if (!ast->cmd2 || !ast->cmd2[0])
				return ;
			if (is_bult_in(ast->cmd2) == 1)
			{
				redirection(ast);
				*error_code = exec_bult_in(ast->cmd2, env, error_code);
				restore_redirection(ast);
			}
			else
				*error_code = exec_cmd(ast, env);
		}
		if (ast->type == AST_PIPE)
			exec_pipe(ast, env, error_code, global);
		if (ast->type == AST_AND)
			exec_and(ast, env, error_code, global);
		if (ast->type == AST_OR)
			exec_or(ast, env, error_code, global);
		if (ast->type == AST_SUBSHELL)
			exec_subshell(ast, env, error_code, global);
	}
}

void	execution(t_global *global)
{
	execution_2(global->ast, global->env, global->error_code, global);
}

char	*init_path(t_ast **ast, t_env *env)
{
	char	*path;

	path = find_cmd(env, (*ast)->cmd2[0]);
	if (!path)
	{
		write(2, "minishell: ", 11);
		write(2, (*ast)->cmd2[0], ft_strlen((*ast)->cmd2[0]));
		write(2, ": command not found\n", 21);
		return (NULL);
	}
	return (path);
}

void	error_pid(char **paths)
{
	free(*paths);
	perror("fork failed");
	exit (2);
}

void	error_pid_pipe(void)
{
	perror("fork failed");
	exit (2);
}

void	error_pipe(void)
{
	perror("pipe failed");
	exit(2);
}

void	child_cmd(t_ast **ast, char **path)
{
	init_child_signals();
	redirection(*ast);
	execve(*path, (*ast)->cmd2, NULL);
	perror("minishell");
	exit (127);
}

int	exec_cmd(t_ast *ast, t_env *env)
{
	char	*path;
	pid_t	pid;
	int		status;

	g_signal = 1;
	status = 0;
	path = init_path(&ast, env);
	if (!path)
		return (127);
	pid = fork();
	if (pid == -1)
		error_pid(&path);
	if (pid == 0)
		child_cmd(&ast, &path);
	free(path);
	waitpid(pid, &status, 0);
	signal(SIGINT, handler);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
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

void	exec_pipe(t_ast *ast, t_env *env, int *error_code, t_global *global)
{
	int		fd[2];
	pid_t	pid[2];
	int		status;

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
	execution_2(ast->left, env, error_code, global);
	if (*error_code == 0)
		execution_2(ast->right, env, error_code, global);
}

void	exec_or(t_ast *ast, t_env *env, int *error_code, t_global *global)
{
	execution_2(ast->left, env, error_code, global);
	if (*error_code != 0)
		execution_2(ast->right, env, error_code, global);
}

void	exec_subshell(t_ast *ast, t_env *env, int *error_code, t_global *global)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		printf("error");
	if (pid == 0)
	{
		expand_function(ast, env);
		redirection(ast);
		execution_2(ast->left, env, error_code, global);
		exit (*error_code);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*error_code = (WEXITSTATUS(status));
	return ;
}
