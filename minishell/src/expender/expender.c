/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:29:35 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/31 18:32:05 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*app_expend(char *str, t_global *global, bool state)
{
	if (!str)
		return (NULL);
	if (check_if_expendable(str) == 0)
		return (str);
	else
	{
		if (state == true)
			str = new_string(str, global);
		else if (state == false)
			str = new_string(str, global);
	}
	return (str);
}

void	expand_function(t_ast *ast, t_global *global)
{
	int	len;

	len = 0;
	if (!global)
		return ;
	if (!ast)
		return ;
	if (check_if_word(ast) == 1)
	{
		ast->cmd2 = malloc(sizeof(char *) * (expand_len_token(ast, global)
					+ 1));
		if (!ast->cmd2)
			return ;
		call_expand(ast, global);
	}
	check_redirection(ast, global);
}
