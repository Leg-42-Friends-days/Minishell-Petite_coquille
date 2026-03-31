/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:33:35 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/31 11:15:52 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast	*ast_node(int type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->cmd_token = NULL;
	node->redirs = NULL;
	node->cmd2 = NULL;
	return (node);
}

void	free_sub_redir(t_redir *current)
{
	t_sub_token	*tmpp;
	t_sub_token	*sub_redir;

	tmpp = NULL;
	sub_redir = current->target->sub_token;
	while(sub_redir)
	{
		free(sub_redir->var);
		tmpp = sub_redir->next;
		free(sub_redir);
		sub_redir = tmpp;
	}
}

void	free_parser(t_ast *ast)
{
	t_redir		*current;
	t_redir		*tmp;

	current = NULL;
	tmp = NULL;
	if (!ast)
		return ;
	if (ast->left)
		free_parser(ast->left);
	if (ast->right)
		free_parser(ast->right);
	free_cmd2(ast->cmd2);
	if (ast->redirs)
		current = ast->redirs;
	while (current)
	{
		free_sub_redir(current);
		free(current->target);
		tmp = current->next;
		free(current);
		current = tmp;
	}
	free(ast);
}

void	free_cmd2(char **cmmd)
{
	int	i;

	if (!cmmd)
		return ;
	i = 0;
	while (cmmd[i])
	{
		free(cmmd[i]);
		i++;
	}
	free(cmmd);
}

t_ast	*free_malloc_error(t_ast *node, int *error)
{
	free_parser(node);
	*error = 1;
	return (NULL);
}
