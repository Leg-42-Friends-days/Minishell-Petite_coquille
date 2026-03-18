/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:28:07 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/18 14:55:37 by mickzhan         ###   ########.fr       */
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
		exit_status = function_export(env, cmd[1]);
	printf("CMD %s\n", cmd[1]);
	return (exit_status);
}

void	print_tab(char **tabl)
{
	int	i;

	i = 0;
	while(tabl[i] != NULL)
	{
		printf("%s\n", tabl[i]);
		i++;
	}
}

void	execution_2(t_ast *ast, t_env *env, int *error_code)
{
	if (ast != NULL)
	{
		if (ast->type == AST_CMD)
		{
			expand_function(ast, env);
			//print_tab(ast->cmd2);
			if (!ast->cmd2[0])
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
			exec_pipe(ast, env, error_code);
		if (ast->type == AST_AND)
			exec_and(ast, env, error_code);
		if (ast->type == AST_OR)
			exec_or(ast, env, error_code);
		if (ast->type == AST_SUBSHELL)
			exec_subshell(ast, env, error_code);
	}
}

void	execution(t_global *global)
{
	execution_2(global->ast, global->env, global->error_code);
}

int	exec_cmd(t_ast *ast, t_env *env)
{
	char	*path;
	pid_t	pid;
	int		status;

	g_signal = 1;
	status = 0;
	path = find_cmd(env, ast->cmd2[0]);
	if (!path)
	{
		write(2, "minishell: ", 11);
		write(2, ast->cmd2[0], ft_strlen(ast->cmd2[0]));
		write(2, ": command not found\n", 21);
		return (127);
	}
	pid = fork();
	if (pid == -1)
		printf("error");
	if (pid == 0)
	{
		init_child_signals();
		redirection(ast);
		execve(path, ast->cmd2, NULL);
		perror("minishell");
		exit (127);
	}
	waitpid(pid, &status, 0);
	signal(SIGINT, handler);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

void	exec_pipe(t_ast *ast, t_env *env, int *error_code)
{
	int		fd[2];
	pid_t	pid[2];
	int		status;

	if (pipe(fd) == -1)
	{
		perror("pipe failed");
		exit (2);
	}
	pid[0] = fork();
	//if (pid == -1)
	//	erreur;
	if (pid[0] == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		execution_2(ast->left, env, error_code);
		exit(0);
	}
	pid[1] = fork();
	//if (pid == -1)
	//	erreur;
	if (pid[1] == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		execution_2(ast->right, env, error_code);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);
	if (WIFEXITED(status))
		*error_code = (WEXITSTATUS(status));
	return ;
}

void	exec_and(t_ast *ast, t_env *env, int *error_code)
{
	execution_2(ast->left, env, error_code);
	if (*error_code == 0 )
		execution_2(ast->right, env, error_code);
}

void	exec_or(t_ast *ast, t_env *env, int *error_code)
{
	execution_2(ast->left, env, error_code);
	if (*error_code != 0 )
		execution_2(ast->right, env, error_code);
}

void	exec_subshell(t_ast *ast, t_env *env, int *error_code)
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
		execution_2(ast->left, env, error_code);
		exit (*error_code);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*error_code = (WEXITSTATUS(status));
	return ;
}

