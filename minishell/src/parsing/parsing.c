/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:05:38 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/20 14:43:43 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast	*parse_cmd(t_token **token, t_global *global)
{
	t_ast	*node;
	int		error_code;

	node = NULL;
	error_code = parse_subshell(&node, token, global);
	if (error_code == 1)
		return (free_malloc_error(node));
	if (error_code == 2)
		return (node);
	error_code = redir_before_word(&node, token, global);
	if (error_code > 0)
	{
		if (error_code == 1)
			return (free_malloc_error(node));
	}
	else if (*token && (*token)->type == WORD)
	{
		node = ast_node(AST_CMD);
		if (!node)
			return (free_malloc_error(node));
		node->cmd_token = *token;
	}
	if (redir_after_word(&node, token) == 1)
		return (free_malloc_error(node));
	return (node);
}

t_ast	*parse_pipe(t_token **token, t_global *global)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_cmd(token, global);
	while (*token && (*token)->type == PIPE)
	{
		node = ast_node(AST_PIPE);
		if (!node)
			return (free_malloc_error(left));
		*token = (*token)->next;
		node->left = left;
		node->right = parse_cmd(token, global);
		left = node;
	}
	return (left);
}

t_ast	*parse_and(t_token **token, t_global *global)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_pipe(token, global);
	while (*token && (*token)->type == AND)
	{
		node = ast_node(AST_AND);
		if (!node)
			return (free_malloc_error(left));
		*token = (*token)->next;
		node->left = left;
		node->right = parse_pipe(token, global);
		left = node;
	}
	return (left);
}

t_ast	*parse_or(t_token **token, t_global *global)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_and(token, global);
	while (*token && (*token)->type == OR)
	{
		node = ast_node(AST_OR);
		if (!node)
			return (free_malloc_error(left));
		*token = (*token)->next;
		node->left = left;
		node->right = parse_and(token, global);
		left = node;
	}
	return (left);
}

/* void	print_ast(t_ast *ast)
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

t_ast	*parser(t_token **token, t_global *global)
{
	t_ast	*ast;

	if (!token || !*token)
		return (0);
	ast = NULL;
	if (check_token((*token)) == 1)
	{
		write(2, "Minishell : syntax error near unexpected '", 42);
		write(2, (*token)->sub_token->var, ft_strlen((*token)->sub_token->var));
		write(2, "'\n", 2);
		return (NULL);
	}
	ast = parse_or(token, global);
	//print_ast(ast);
	return (ast);
}
