/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:32:52 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/01 10:19:26 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redir(t_token *token)
{
	if (token && (token->type == INFILE || token->type == OUTFILE
			|| token->type == APPEND || token->type == HEREDOC))
		return (1);
	else
		return (0);
}

int	subshell_redirs(t_ast *node, t_token **token, t_global *global)
{
	if (is_redir(*token))
	{
		if ((token_list_redir(token, node, global)) == 1)
			return (1);
		while (is_redir(*token))
		{
			if ((token_list_redir(token, node, global)) == 1)
				return (1);
		}
		if (*token)
			node->cmd_token = *token;
	}
	while (*token && (*token)->type < 5)
	{
		if (is_redir(*token))
		{
			if ((token_list_redir(token, node, global)) == 1)
				return (1);
		}
		else if (*token)
			*token = (*token)->next;
	}
	return (0);
}

int	parse_subshell(t_ast **node, t_token **token, t_global *g, int *error)
{
	if (*token && (*token)->type == L_PAR)
	{
		*node = ast_node(AST_SUBSHELL);
		if (!*node)
			return (1);
		*token = (*token)->next;
		(*node)->left = parse_or_and(token, g, error);
		if (!(*node)->left)
			return (1);
		(*node)->right = NULL;
		if (*token && (*token)->type == R_PAR)
			*token = (*token)->next;
		else
		{
			write(2, "minishell: syntax error: unclosed parenthesis\n", 46);
			return (1);
		}
		if (subshell_redirs(*node, token, g) == 1)
			return (1);
		return (2);
	}
	return (0);
}

int	redir_before_word(t_ast **node, t_token **token, t_global *global)
{
	t_token	*save;

	save = *token;
	if (is_redir(*token))
	{
		*node = ast_node(AST_CMD);
		if ((token_list_redir(token, *node, global)) == 1)
			return (1);
		while (is_redir(*token))
		{
			if (global->what_free == 1)
				global->head = *token;
			if ((token_list_redir(token, *node, global)) == 1)
				return (1);
		}
		if (*token)
			(*node)->cmd_token = *token;
		if (global->what_free == 1)
		{
			global->what_free = global->what_free + 1;
			global->head = *token;
		}
		return (2);
	}
	return (0);
}

int	redir_after_word(t_ast **node, t_token **token, t_global *global)
{
	while (*token && (*token)->type < 5)
	{
		if (is_redir(*token))
		{
			if ((token_list_redir(token, *node, global)) == 1)
				return (1);
		}
		else
			*token = (*token)->next;
	}
	return (0);
}
