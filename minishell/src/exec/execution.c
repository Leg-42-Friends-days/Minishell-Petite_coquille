/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:28:07 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/04 16:04:13 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_bult_in(char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		return (1);
	return (0);
}

int	exec_bult_in(char **cmd, t_env *env)
{
	int	exit_status;
	
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		exit_status = ft_echo(cmd);
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		exit_status = ft_cd(cmd, env);
	if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		exit_status = ft_pwd(cmd, env);
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

int	execution(t_ast *ast, t_env *env)
{
	int	exit_status;

	exit_status = 0;
	if (ast != NULL)
	{
		if (ast->type == AST_CMD)
		{
			expand_function(ast, env);
			//print_tab(ast->cmd2);
			if (is_bult_in(ast->cmd2) == 1)
			{
				redirection(ast);
				exit_status = exec_bult_in(ast->cmd2, env);
				restore_redirection(ast);
			}
			else
				exit_status = exec_cmd(ast, env);
		}
		if (ast->type == AST_PIPE)
			exit_status = exec_pipe(ast, env);
		if (ast->type == AST_AND)
			exit_status = exec_and(ast, env);
		if (ast->type == AST_OR)
			exit_status = exec_or(ast, env);
		if (ast->type == AST_SUBSHELL)
			exit_status = exec_subshell(ast, env);
	}
	return (exit_status);
	printf("\n");
}
int	exec_cmd(t_ast *ast, t_env *env)
{
	char	*path;
	pid_t	pid;
	int		status;

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
		redirection(ast);
		execve(path, ast->cmd2, NULL);
		perror("minishell");
		exit (127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	exec_pipe(t_ast *ast, t_env *env)
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
		execution(ast->left, env);
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
		execution(ast->right, env);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return(0);
}

int	exec_and(t_ast *ast, t_env *env)
{
	int	exit_status;

	exit_status = execution(ast->left, env);
	if (exit_status == 0 )
		exit_status = execution(ast->right, env);
	return (exit_status);
}

int	exec_or(t_ast *ast, t_env *env)
{
	int	exit_status;

	exit_status = execution(ast->left, env);
	if (exit_status != 0 )
		exit_status = execution(ast->right, env);
	return (exit_status);
}

int	exec_subshell(t_ast *ast, t_env *env)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	pid = fork();
	if (pid == -1)
		printf("error");
	if (pid == 0)
	{
		expand_function(ast, env);
		redirection(ast);
		exit_code = execution(ast->left, env);
		exit (exit_code);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

