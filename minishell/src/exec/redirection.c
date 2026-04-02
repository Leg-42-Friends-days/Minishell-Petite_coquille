/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:01:11 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/02 20:37:52 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	dollar_before_quote(t_sub_token *current)
{
	int	len;

	len = ft_strlen(current->var);
	if (current->next)
	{
		if (current->next->var)
		{
			if (current->var[len - 1] == '$')
			{
				if (len > 1 && current->var[len - 2] == '$')
					return ;
				current->var[len - 1] = '\0';
			}
		}
	}
}

void	join_sub_token_limiter(t_sub_token **c, char **result, char **first)
{
	dollar_before_quote((*c)->next);
	*result = ft_strjoin(*first, (*c)->next->var);
	if (*first)
		free(*first);
	*first = *result;
	if ((*c)->next->quote != NONE)
		(*c)->quote = (*c)->next->quote;
}

void	join_limiter(t_redir *node)
{
	char		*result;
	char		*first;
	t_sub_token	*current;
	t_sub_token	*next;

	result = NULL;
	first = NULL;
	next = NULL;
	current = node->target->sub_token;
	first = node->target->sub_token->var;
	dollar_before_quote(current);
	while (current)
	{
		if (current->next)
		{
			if (current->next->var)
				join_sub_token_limiter(&current, &result, &first);
		}
		next = current->next;
		current = next;
	}
	if (result)
		node->target->sub_token->var = result;
}

int	redirection(t_ast *node, t_global *global)
{
	t_redir	*current;
	int		code;

	code = 0;
	current = node->redirs;
	if (!current)
		return (0);
	current->stdin = dup(0);
	current->stdout = dup(1);
	while (current)
	{
		if (current->type == INFILE)
			redir_stdin(current, global, &code);
		else if (current->type == OUTFILE)
			redir_stdout_trunc(current, global, &code);
		else if (current->type == HEREDOC)
			redir_here_doc(current, global, &code);
		else if (current->type == APPEND)
			redir_stdout_append(current, global, &code);
		if (code != 0)
			return (1);
		current = current->next;
	}
	return (0);
}

void	restore_redirection(t_ast *node)
{
	t_redir	*current;	

	current = node->redirs;
	if (!current)
		return ;
	while (current)
	{
		if (current->stdin != -1)
		{
			dup2(current->stdin, 0);
			close(current->stdin);
		}
		if (current->stdout != -1)
		{
			dup2(current->stdout, 1);
			close(current->stdout);
		}
		if (current->fd > 2)
			close(current->fd);
		current = current->next;
	}
}
