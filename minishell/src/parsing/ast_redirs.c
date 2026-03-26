/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:04:21 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/26 15:52:49 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_no_target(t_global *global)
{
	write(2, "minishell: syntax error near unexpected token `newline'\n", 56);
	*global->error_code = 2;
	return (1);
}

int	redir_node(t_redir **redir, t_token **token, t_global *global)
{
	t_redir	*node;
	t_token	*file;
	t_redir	*current;

	if (!(*token)->next)
		return (error_no_target(global));
	node = malloc(sizeof(t_redir));
	if (!node)
		return (1);
	node->type = (*token)->type;
	file = (*token)->next;
	node->target = file;
	node->next = NULL;
	node->stdin = -1;
	node->stdout = -1;
	node->fd = 0;
	if (!redir || !(*redir))
	{
		(*redir) = node;
		return (0);
	}
	current = *redir;
	while (current->next != NULL)
		current = current->next;
	current->next = node;
	return (0);
}

void	fill_redir(t_token *r, t_token *f, t_token *p, t_token *n)
{
	r->next = NULL;
	r->prev = NULL;
	ft_minidelone(r->sub_token);
	free(r);
	f->prev = NULL;
	f->next = NULL;
	if (p)
		p->next = n;
	if (n)
		n->prev = p;
}

int	token_list_redir(t_token **token, t_ast *node, t_global *global)
{
	t_token	*redir;
	t_token	*file;
	t_token	*prev;
	t_token	*next;

	if ((*token)->prev)
		prev = (*token)->prev;
	else
		prev = NULL;
	if ((redir_node(&node->redirs, token, global)) == 1)
		return (1);
	redir = (*token);
	file = redir->next;
	*token = (*token)->next;
	if ((*token)->next)
		next = (*token)->next;
	else
		next = NULL;
	fill_redir(redir, file, prev, next);
	if (next)
		(*token) = next;
	else
		(*token) = NULL;
	return (0);
}
