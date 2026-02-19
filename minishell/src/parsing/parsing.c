/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:05:38 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/19 17:55:37 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parser.h"

/* t_token	*lstfirst_token(t_token *lst)
{
	t_token	*cursor;

	if (!lst || !lst->sub_token)
		return (lst);
	cursor = lst;
	while (cursor->sub_token->prev != NULL)
		cursor->sub_token = cursor->sub_token->prev;
	return (cursor);
} */

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

void	redir_node(t_redir **redir, t_token **token)
{
	t_redir	*node;
	t_token	*file;

	node = malloc(sizeof(t_redir));
	if (!node)
		return ;
	node->type = (*token)->type;
	file = (*token)->next;
	node->target = file;
	node->next = NULL;
	if (!redir || !(*redir))
	{
		(*redir) = node;
		return;
	}
	while ((*redir)->next != NULL)
	{
		(*redir) = (*redir)->next;
	}
	(*redir)->next = node;
}

void	token_list_redir(t_token **token, t_ast *node)
{
	t_token	*prev;
	t_token	*next;
	t_token	*redir;
	t_token	*file;

	if ((*token)->prev)
		prev = (*token)->prev;
	else
		prev = NULL;
	redir_node(&node->redirs, token);;
	//node->redirs->type = (*token)->type;
	file = (*token)->next;
	redir = (*token);
	*token = (*token)->next;
	if ((*token)->next)
		next = (*token)->next;
	else 
		next = NULL;
	redir->next = NULL;
	redir->prev = NULL;
	ft_minidelone(redir->sub_token);
	free(redir);
	file->prev = NULL;
	file->next = NULL;
	//node->redirs->target = file; 
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	if (next)
		(*token) = next;
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
	if (*token && ((*token)->type == INFILE || (*token)->type == OUTFILE || (*token)->type == APPEND || (*token)->type == HEREDOC))
	{
		node = ast_node(AST_CMD);
		token_list_redir(token, node);
		node->cmd_token = *token;
	}
	else if (*token && (*token)->type == WORD)
	{
		node = ast_node(AST_CMD);
		node->cmd_token = *token;
	}
	while (*token && (*token)->type < 5)
	{
		if (*token && ((*token)->type == INFILE || (*token)->type == OUTFILE || (*token)->type == APPEND || (*token)->type == HEREDOC))
		{
			token_list_redir(token, node);
		}
		else
			*token = (*token)->next;
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

void	print_ast(t_ast *ast)
{
	if (ast != NULL)
	{
		printf("%u\n", ast->type);
		if (ast->cmd_token)
		{
			while (ast->cmd_token && ast->cmd_token->type < 5)
			{
				printf("AST CONTENT : %s\n", ast->cmd_token->sub_token->var);
				if (ast->cmd_token->next)
					ast->cmd_token = ast->cmd_token->next;
				else
					break ;
			}
			while (ast->redirs)
			{
				printf("REDIR VALUE : %u\n", ast->redirs->type);
				printf("REDIR CONTENT : %s\n", ast->redirs->target->sub_token->var);
				if (ast->redirs->next)
					ast->redirs = ast->redirs->next;
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

int	parser(t_token **token)
{
	t_ast	*ast;

	if (!token || !*token)
		return (0);
	ast = NULL;
	if (check_token((*token)) == 1)
	{
		ft_printf(2, "PRINTF TESTER : syntax error near unexpected token\n");
		return (2);
	}
	ast = parse_or(token);
	print_ast(ast);
	return (0);
}
