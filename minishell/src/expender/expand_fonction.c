/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_fonction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 18:01:12 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/31 18:07:01 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	double_quote(t_ast *ast, t_global *global, t_sub_token *sub, int *index)
{
	char	*tmp;

	tmp = ft_strdup(sub->var);
	if (!tmp)
		return ;
	tmp = app_expend(tmp, global, true);
	if (!tmp)
		return ;
	add_str_to_cmd(ast, index, tmp);
	free(tmp);
}

void	single_quote(t_ast *ast, t_sub_token *sub, int *index)
{
	add_str_to_cmd(ast, index, sub->var);
}

void	normal_quote(t_ast *ast, t_global *global, t_sub_token *sub, int *index)
{
	char	*tmp;
	char	**split;
	int		space;

	tmp = normal_value(sub, global);
	if (!tmp)
		return ;
	if (check_if_next_token_wild(sub) && !check_if_wildcard(tmp)
		&& ft_strchr(tmp, ' ') == NULL)
	{
		add_index(ast, index);
		*index = expand_wildcard(tmp, ast, index);
		ast->cmd2[*index] = NULL;
		return (free(tmp));
	}
	space = (ft_strchr(tmp, ' ') != NULL);
	if (!space)
		return (add_str_to_cmd(ast, index, tmp), free(tmp));
	if (sub->prev && (sub->prev->quote == DOUBLE || sub->prev->quote == SINGLE))
		add_index(ast, index);
	split = ft_split(tmp, ' ');
	free(tmp);
	if (!split)
		return ;
	(add_split_words(ast, split, index), free_split(split));
}

void	expand_token(t_ast *ast, t_global *global, t_token *current_token,
		int *index)
{
	t_sub_token	*current_sub;

	ast->cmd2[*index] = NULL;
	current_sub = current_token->sub_token;
	while (current_sub != NULL)
	{
		if (!check_dollars(current_sub))
		{
			if (current_sub->quote == DOUBLE)
				double_quote(ast, global, current_sub, index);
			else if (current_sub->quote == SINGLE)
				single_quote(ast, current_sub, index);
			else if (current_sub->quote == NORMAL)
				normal_quote(ast, global, current_sub, index);
		}
		current_sub = current_sub->next;
	}
	add_index(ast, index);
}

void	call_expand(t_ast *ast, t_global *global)
{
	t_token	*current_token;
	int		index;

	index = 0;
	current_token = ast->cmd_token;
	while (current_token != NULL && current_token->type == WORD)
	{
		expand_token(ast, global, current_token, &index);
		current_token = current_token->next;
	}
	ast->cmd2[index] = NULL;
}
