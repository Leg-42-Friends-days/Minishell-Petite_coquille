/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:33:35 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/24 15:06:21 by ibrouin-         ###   ########.fr       */
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

void	free_parser(t_ast *ast)
{
	t_redir	*current;
	t_redir	*tmp;

	if (!ast)
		return ;
	if (ast->left)
		free_parser(ast->left);
	if (ast->right)
		free_parser(ast->right);
	free_cmd2(ast->cmd2);
	current = ast->redirs;
	while (current)
	{
		free(current->target->sub_token->var);
		free(current->target->sub_token);
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
	//write(2, "minishell: cannot allocate memory\n", 34);
	*error = 1;
	free_parser(node);
	return (NULL);
}
