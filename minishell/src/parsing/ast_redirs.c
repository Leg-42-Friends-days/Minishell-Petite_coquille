/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:04:21 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/18 20:45:32 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

//void	error_no_target()

int	redir_node(t_redir **redir, t_token **token)
{
	t_redir	*node;
	t_token	*file;
	t_redir	*current;

	if (!(*token)->next)
	{
		write(2, "minishell: syntax error near unexpected token `newline'\n", 56);
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
		current = current->next;
	current->next = node;
	return (0);
}

int	token_list_redir(t_token **token, t_ast *node)
{
	t_token	*redir;
	t_token	*file;
	t_token	*prev;
	t_token	*next;

	if ((*token)->prev)
		prev = (*token)->prev;
	else
		prev = NULL;
	if ((redir_node(&node->redirs, token)) == 1)
		return (1);
	redir = (*token);
	file = redir->next;
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
