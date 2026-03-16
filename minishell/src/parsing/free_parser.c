/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:04:21 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/16 17:13:11 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"

void	ft_miniclear_parse(t_token *lst)
{
	t_token		*cursor;
	t_sub_token	*sub_cursor;
	t_sub_token	*sub_next;
	t_token		*next;

	if (!lst)
		return ;
	cursor = lst;
	while (cursor)
	{
		if (!cursor->sub_token)
			return ;
		sub_cursor = cursor->sub_token;
		while (sub_cursor)
		{
			sub_next = sub_cursor->next;
			ft_minidelone(sub_cursor);
			sub_cursor = sub_next;
		}
		if(!cursor->next)
			return ;
		next = cursor->next;
		free(cursor);
		cursor = next;
	}
	lst = NULL;
}

void    free_parser(t_ast *ast)
{
	if (ast != NULL)
	{
		if (ast->left)
			free_parser(ast->left);
		if (ast->right)
			free_parser(ast->right);
		free_cmd(ast->cmd);
		free_cmd(ast->cmd2);
		if (ast->redirs)
		{
			free(ast->redirs->target->sub_token->var);
			free(ast->redirs->target->sub_token);
			free(ast->redirs->target);
			free(ast->redirs);
			//ft_minidelone(ast->redirs->target->sub_token);
			//free(ast->redirs->target);
		}
	}
	free(ast);
}

void    free_cmd(char **cmmd)
{
	int i;
	
	if (!cmmd || !*cmmd)
		return ;
	i = 0;
	while (cmmd[i])
	{
		free(cmmd[i]);
		i++;
	}
	free(cmmd);
}