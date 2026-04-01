/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:35:43 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/01 11:38:45 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../minishell.h"

void	*ft_malloc(size_t size)
{
	static int	count = 0;

	count++;
	if (count == 5)
	{
		return (NULL);
	}
	return (malloc(size));
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
/* 
void	print_ast(t_ast *ast)
{
	if (ast != NULL)
	{
		if (ast->type)
			printf("%u\n", ast->type);
		if (ast->cmd_token)
		{
			while (ast->cmd_token && ast->cmd_token->type < 5)
			{
				if (ast->cmd_token->sub_token->var)
					printf("AST CONTENT : %s\n", ast->cmd_token->sub_token->var);
				if (ast->cmd_token->next)
					ast->cmd_token = ast->cmd_token->next;
				else
					break ;
			}
		}
		if (ast->redirs)
		{
			while (ast->redirs)
			{
				if (ast->redirs->type)
					printf("REDIR VALUE : %u\n", ast->redirs->type);
				if (ast->redirs->target->sub_token->var)
					printf("REDIR CONTENT : %s\n", ast->redirs->target->sub_token->var);
				if (ast->redirs->next)
					ast->redirs = ast->redirs->next;
				else
					break ;
			}
		}
		if (ast->left)
			print_ast(ast->left);
		if (ast->right)
			print_ast(ast->right);
		printf("\n");
	}
} */
