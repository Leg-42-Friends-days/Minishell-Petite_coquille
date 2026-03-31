/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:44:26 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/31 17:54:57 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_redir(t_sub_token *sub, t_global *global)
{
	char	*part;

	part = ft_strdup(sub->var);
	if (!part)
		return (NULL);
	if (sub->quote != SINGLE && check_if_expendable(part) == true)
		part = app_expend(part, global, sub->quote == DOUBLE);
	return (part);
}

bool	append_redir(char **content, t_sub_token *sub, t_global *global)
{
	char	*part;
	char	*str;

	part = expand_redir(sub, global);
	if (!part)
		return (false);
	str = ft_strjoin(*content, part);
	free(*content);
	free(part);
	if (!str)
		return (false);
	*content = str;
	return (true);
}

char	*redir_target(t_sub_token *sub, t_global *global)
{
	char	*content;

	content = ft_strdup("");
	if (!content)
		return (NULL);
	while (sub)
	{
		if (check_dollars(sub))
		{
			sub = sub->next;
			continue ;
		}
		if (append_redir(&content, sub, global) == 0)
			return (free(content), NULL);
		sub = sub->next;
	}
	return (content);
}

void	check_redirection(t_ast *ast, t_global *global)
{
	t_redir		*re;
	char		*content;

	if (!ast || !ast->redirs)
		return ;
	re = ast->redirs;
	while (re != NULL)
	{
		if (re->target && re->target->sub_token && re->target->sub_token->var)
		{
			content = redir_target(re->target->sub_token, global);
			if (content)
			{
				free(re->target->sub_token->var);
				re->target->sub_token->var = content;
			}
		}
		re = re->next;
	}
}
