/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:53:43 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/01 11:54:16 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	close_saved_fd(t_ast *ast)
{
	t_redir	*current;

	if (!ast)
		return ;
	current = ast->redirs;
	while (current)
	{
		if (current->stdin != -1)
			close(current->stdin);
		if (current->stdout != -1)
			close(current->stdout);
		if (current->fd != -1)
			close(current->fd);
		current = current->next;
	}
	close_saved_fd(ast->left);
	close_saved_fd(ast->right);
}

void	free_before_execute(t_global *global, int error_code)
{
	if (global->what_free > 0)
		global->true_head = global->head;
	ft_miniclear(&(global->true_head));
	free_parser(global->ast);
	if (global->env)
		free_env(global->env);
	free(global);
	exit (error_code);
}
