/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 13:45:55 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/01 11:50:29 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	error_pid(void)
{
	perror("fork failed");
	exit (2);
}

void	error_pipe(void)
{
	perror("pipe failed");
	exit(2);
}

int	free_all_in_child(t_global *global, char **table)
{
	int	error;

	if (global->what_free > 0)
		global->true_head = global->head;
	ft_miniclear(&(global->true_head));
	free_parser(global->ast);
	if (global->env)
		free_env(global->env);
	if (table)
		free_table(table);
	error = global->error_code;
	free(global);
	return (error);
}

int	free_all_pipe_subshell(t_global *global)
{
	int	error;

	if (global->what_free > 0)
		global->true_head = global->head;
	ft_miniclear(&(global->true_head));
	free_parser(global->ast);
	if (global->env)
		free_env(global->env);
	error = global->error_code;
	free(global);
	return (error);
}

void	free_subshell(t_global *global)
{
	int	error;

	error = 0;
	if (global->what_free > 0)
		global->true_head = global->head;
	ft_miniclear(&(global->true_head));
	free_parser(global->ast);
	if (global->env)
		free_env(global->env);
	error = global->error_code;
	free(global);
	exit(error);
}
