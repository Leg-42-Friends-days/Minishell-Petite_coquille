/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:05:38 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/24 18:48:03 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast	*parse_cmd(t_token **token, t_global *global, int *error)
{
	t_ast	*node;
	int		error_code;

	node = NULL;
	error_code = parse_subshell(&node, token, global, error);
	//*error = error_code;
	if (error_code == 1)
		return (free_malloc_error(node, error));
	if (error_code == 2)
		return (node);
	error_code = redir_before_word(&node, token, global);
	//*error = error_code;
	if (error_code > 0)
	{
		if (error_code == 1)
			return (free_malloc_error(node, error));
	}
	else if (*token && (*token)->type == WORD)
	{
		node = ast_node(AST_CMD);
		if (!node)
			return (free_malloc_error(node, error));
		node->cmd_token = *token;
	}
	if (redir_after_word(&node, token, global) == 1)
		return (free_malloc_error(node, error));
	return (node);
}

t_ast	*parse_pipe(t_token **token, t_global *global, int *error)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_cmd(token, global, error);
	while (*token && (*token)->type == PIPE)
	{
		node = ast_node(AST_PIPE);
		if (!node)
			return (free_malloc_error(left, error));
		*token = (*token)->next;
		node->left = left;
		node->right = parse_cmd(token, global, error);
		left = node;
	}
	return (left);
}

t_ast	*parse_or_and(t_token **token, t_global *global, int *error)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_pipe(token, global, error);
	while (*token && ((*token)->type == OR || (*token)->type == AND))
	{
		if ((*token)->type == AND)
			node = ast_node(AST_AND);
		if ((*token)->type == OR)
			node = ast_node(AST_OR);
		if (!node)
			return (free_malloc_error(left, error));
		*token = (*token)->next;
		node->left = left;
		node->right = parse_pipe(token, global, error);
		left = node;
	}
	return (left);
}

int	parser(t_token **token, t_global *global)
{
	t_token	*current;
	int		error;

	error = 0;
	if (!token || !*token)
		return (0);
	current = (*token);
	if (check_token((&current)) == 1)
	{
		write(2, "Minishell : syntax error near unexpected '", 42);
		write(2, current->sub_token->var, ft_strlen(current->sub_token->var));
		write(2, "'\n", 2);
		*global->error_code = 2;
		return (1);
	}
	global->ast = parse_or_and(token, global, &error);
	if (error != 0)
		return (1);
	//print_ast(global->ast);
	return (0);
}
