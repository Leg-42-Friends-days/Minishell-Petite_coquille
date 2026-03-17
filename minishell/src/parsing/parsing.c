/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:05:38 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/17 21:04:17 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	node->cmd = NULL;
	node->cmd2 = NULL;
	return (node);
}

int	redir_node(t_redir **redir, t_token **token)
{
	t_redir	*node;
	t_token	*file;
	t_redir	*current;

	if (!(*token)->next)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	node = malloc(sizeof(t_redir));
	if (!node)
		return (1);
	node->type = (*token)->type;
	file = (*token)->next;
	node->target = file;
	node->next = NULL;
	if (!redir || !(*redir))
	{
		(*redir) = node;
		return (0);
	}
	current = *redir;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = node;
	return (0);
}

int	token_list_redir(t_token **token, t_ast *node)
{
	t_token	*prev;
	t_token	*next;
	t_token	*redir;
	t_token	*file;

	if ((*token)->prev)
		prev = (*token)->prev;
	else
		prev = NULL;
	if ((redir_node(&node->redirs, token)) == 1)
		return (1);
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
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	if (next)
		(*token) = next;
	else
		(*token) = NULL;
	return (0);
}

int	subshell_redirs(t_ast *node, t_token **token)
{
	if (*token && ((*token)->type == INFILE || (*token)->type == OUTFILE || (*token)->type == APPEND || (*token)->type == HEREDOC))
		{
			if ((token_list_redir(token, node)) == 1)
				return (1);
			while (*token && ((*token)->type == INFILE || (*token)->type == OUTFILE || (*token)->type == APPEND || (*token)->type == HEREDOC))
			{
				if ((token_list_redir(token, node)) == 1)
				return (1);
			}
			if (*token)
				node->cmd_token = *token;
		}
		while (*token && (*token)->type < 5)
		{
			if (*token && ((*token)->type == INFILE || (*token)->type == OUTFILE || (*token)->type == APPEND || (*token)->type == HEREDOC))
			{
				if ((token_list_redir(token, node)) == 1)
					return (1);
			}
			else if (*token)
				*token = (*token)->next;
		}
		return (0);
}

int	redir_before_word(t_ast *node, t_token **token)
{
	if (*token && ((*token)->type == INFILE || (*token)->type == OUTFILE || (*token)->type == APPEND || (*token)->type == HEREDOC))
	{
		node = ast_node(AST_CMD);
		if ((token_list_redir(token, node)) == 1)
			return (1);
		while (*token && ((*token)->type == INFILE || (*token)->type == OUTFILE || (*token)->type == APPEND || (*token)->type == HEREDOC))
		{
			if ((token_list_redir(token, node)) == 1)
			return (1);
		}
		if (*token)
			node->cmd_token = *token;
	}
	return (0);
}

t_ast	*parse_cmd(t_token **token)
{
	t_ast	*node;

	//node = NULL;
	if (*token && (*token)->type == L_PAR)
	{
		node = ast_node(AST_SUBSHELL);
		*token = (*token)->next;
		node->left = parse_or(token);
		node->right = NULL;
		if (*token && (*token)->type == R_PAR)
			*token = (*token)->next;
		else
		{
			ft_printf(2, "PRINTF TESTERrrr : syntax error near unexpected token\n");
			return (NULL);
		}
		if (subshell_redirs(node, token) == 1)
			return (NULL);
		return (node);
	}
	if (*token && ((*token)->type == INFILE || (*token)->type == OUTFILE || (*token)->type == APPEND || (*token)->type == HEREDOC))
	{
		node = ast_node(AST_CMD);
		if ((token_list_redir(token, node)) == 1)
			return (NULL);
		while (*token && ((*token)->type == INFILE || (*token)->type == OUTFILE || (*token)->type == APPEND || (*token)->type == HEREDOC))
		{
			if ((token_list_redir(token, node)) == 1)
			return (NULL);
		}
		if (*token)
			node->cmd_token = *token;
	}
	//if (redir_before_word(node, token) == 1)
	//	return (NULL);
	else if (*token && (*token)->type == WORD)
	{
		node = ast_node(AST_CMD);
		node->cmd_token = *token;
	}
	while (*token && (*token)->type < 5)
	{
		if (*token && ((*token)->type == INFILE || (*token)->type == OUTFILE || (*token)->type == APPEND || (*token)->type == HEREDOC))
		{
			if ((token_list_redir(token, node)) == 1)
				return (NULL);
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
/* 	if (ast->left)
			print_ast(ast->left);
	if (ast->right)
		print_ast(ast->right);
	printf("\n"); */
}

t_ast	*parser(t_token **token)
{
	t_ast	*ast;

	if (!token || !*token)
		return (0);
	ast = NULL;
	if (check_token((*token)) == 1)
	{
		ft_printf(2, "Minishell : syntax error near unexpected '%s'\n", (*token)->sub_token->var);
		return (NULL);
	}
	ast = parse_or(token);
	//print_ast(ast);
	return (ast);
}
