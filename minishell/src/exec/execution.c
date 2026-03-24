/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:28:07 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/24 22:55:54 by ibrouin-         ###   ########.fr       */
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

int	exec_bult_in(char **cmd, t_env *env, int *error_code, t_global *global)
{
	int	exit_status;

	exit_status = 0;
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		exit_status = ft_echo(cmd, env);
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		exit_status = ft_cd(cmd, env);
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		exit_status = ft_pwd(cmd, env);
	if (ft_strncmp(cmd[0], "exit", 5) == 0)
		exit_status = ft_exit(cmd, env, error_code, global);
	if (ft_strncmp(cmd[0], "export", 7) == 0)
		exit_status = function_export(env, cmd);
	if (ft_strncmp(cmd[0], "env", 4) == 0)
		exit_status = affichage_env(env);
	if (ft_strncmp(cmd[0], "unset", 6) == 0)
		exit_status = function_unset(env, cmd);
	return (exit_status);
}

void	execution_2(t_ast *ast, t_env *env, int *error_code, t_global *global)
{

	if (ast != NULL)
	{
		if (ast->type == AST_CMD)
		{
			expand_function(ast, global);
			if ((!ast->cmd2 || !ast->cmd2[0]) && ast->redirs)
			{
				global->true_head = global->mini_vars;
				redirection(ast);
				close_saved_fd(ast);
				global->head = global->true_head;
				return;
			}
			else if ((!ast->cmd2 || !ast->cmd2[0]) && !ast->redirs)
				return ;
			//print_tab(ast->cmd2);
			if (is_bult_in(ast->cmd2) == 1)
			{
				redirection(ast);
				*error_code = exec_bult_in(ast->cmd2, env, error_code, global);
				restore_redirection(ast);
			}
			else
				*error_code = exec_cmd(ast, env, global);
		}
		if (ast->type == AST_PIPE)
			exec_pipe(ast, env, error_code, global);
		if (ast->type == AST_AND)
			exec_and(ast, env, error_code, global);
		if (ast->type == AST_OR)
			exec_or(ast, env, error_code, global);
		if (ast->type == AST_SUBSHELL)
			exec_subshell(ast, env, error_code, global);
		//if (ast->type == )
	}
}

void	execution(t_global *global)
{
	execution_2(global->ast, global->env, global->error_code, global);
}
