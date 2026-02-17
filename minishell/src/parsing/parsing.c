/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:05:38 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/17 15:15:41 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*lstfirst_token(t_token *lst)
{
	t_token	*cursor;

	if (!lst || !lst->sub_token)
		return (lst);
	cursor = lst;
	while (cursor->sub_token->prev != NULL)
		cursor->sub_token = cursor->sub_token->prev;
	return (cursor);
}

// Creation de node
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
	return (node);
}

t_ast	*parse_cmd(t_token **token)
{
	t_ast	*node;

	if (*token && (*token)->type == L_PAR)
	{
		node = ast_node(AST_SUBSHELL);
		*token = (*token)->next;
		node->left = parse_or(token);
		node->right = NULL;
		if (*token && (*token)->type == R_PAR)
		{
			*token = (*token)->next;
			return (node);
		}
		else
			ft_printf(2, "PRINTF TESTERrrr : syntax error near unexpected token\n");
	}
	if (*token && (*token)->type == WORD)
	{
		node = ast_node(AST_CMD);
		node->cmd_token = *token;
	}
	while (*token && (*token)->type == WORD)
		*token = (*token)->next;
	while (*token && ((*token)->type == INFILE || (*token)->type == OUTFILE || (*token)->type == APPEND || (*token)->type == HEREDOC))
	{
		node->redirs = malloc(sizeof(t_redir));
		node->redirs->type = (*token)->type;
		*token = (*token)->next;
		node->redirs->target = (*token);
	}
	return (node);
}

t_ast	*parse_pipe(t_token **token)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_cmd(token);
	while (*token && (*token)->type == PIPE)
	{
		node = ast_node(AST_PIPE);
		*token = (*token)->next;
		node->left = left;
		node->right = parse_cmd(token);
		left = node;
	}
	return (left);
}

t_ast	*parse_and(t_token **token)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_pipe(token);
	while (*token && (*token)->type == AND)
	{
		node = ast_node(AST_AND);
		*token = (*token)->next;
		node->left = left;
		node->right = parse_pipe(token);
		left = node;
	}
	return (left);
}

t_ast	*parse_or(t_token **token)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_and(token);
	while (*token && (*token)->type == OR)
	{

		node = ast_node(AST_OR);
		*token = (*token)->next;
		node->left = left;
		node->right = parse_and(token);
		left = node;
	}
	return (left);
}

void	printright(t_ast *ast);

void	print_ast(t_ast *ast)
{
	if (ast != NULL)
	{
		printf("%u\n", ast->type);
		if (ast->cmd_token)
		{
			while (ast->cmd_token && ast->cmd_token->type == WORD)
			{
				printf("AST CONTENT : %s\n", ast->cmd_token->sub_token->var);
				/* if (ast->redirs)
				{
					printf("REDIR VALUE : %u\n", ast->redirs->type);
					printf("REDIR CONTENT : %s\n", ast->redirs->target->sub_token->var);
				} */
				if (ast->cmd_token->next)
					ast->cmd_token = ast->cmd_token->next;
				else
					break ;
			}
		}
	}
	if (ast->left)
		print_ast(ast->left);
	if (ast->right)
		print_ast(ast->right);
	printf("\n");
}

void	printright(t_ast *ast)
{
	while (ast != NULL)
	{
		printf("AST RIGHT VALUE : %u\n", ast->type);
		if (ast->cmd_token)
			printf("AST RIGHT CONTENT : %s\n", ast->cmd_token->sub_token->var);
		// while (ast->cmd_token->sub_token->next != NULL)
		// {
		// 	printf("AST RIGHT TOKEN VALUE : %s \n", ast->cmd_token->sub_token->var);
		// 	ast->cmd_token->sub_token = ast->cmd_token->sub_token->next;
		// }
		ast = ast->right;
	}
}

int	parser(t_token *token)
{
	t_ast	*ast;

	ast = NULL;
	//if (check_token(token) == 1)
	//{
	//	ft_printf(2, "PRINTF TESTER : syntax error near unexpected token\n");
	//	return (2);
	//}
	ast = parse_or(&token);
	print_ast(ast);
	return (0);
}
