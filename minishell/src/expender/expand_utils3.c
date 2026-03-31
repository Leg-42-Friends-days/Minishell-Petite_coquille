/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 18:23:53 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/31 18:24:32 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_if_word(t_ast *ast)
{
	if (ast->type == AST_CMD)
		return (true);
	return (false);
}

bool	check_if_expendable(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != ':' && str[i + 1] != '=' && str[i
				+ 1] != '"' && str[i + 1] != '\'')
			return (true);
		i++;
	}
	return (false);
}

char	*check_string(char *str, t_env *env)
{
	char	*str_env;

	if (!str)
		return (NULL);
	str_env = NULL;
	while (env != NULL)
	{
		if (ft_strncmp(env->key, str, -1) == 0)
		{
			str_env = ft_strdup(env->content);
			break ;
		}
		env = env->next;
	}
	return (str_env);
}

char	*number_str(char *str)
{
	int		i;
	char	*key;

	i = 0;
	if (str[i] >= 48 && str[i] <= 57)
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	if (str[i] >= 48 && str[i] <= 57)
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

bool	check_condition_key(char *str, int i)
{
	if ((str[i] != ' ' && str[i]) && (str[i] != '$' && str[i]) && (str[i] != 34
			&& str[i]) && (str[i] != 39 && str[i]) && (str[i] != '/' && str[i])
		&& (str[i] != '*' && str[i]) && (str[i] && str[i] != ']') && (str[i]
			&& str[i] != '[') && (str[i] && str[i] != '%') && (str[i]
			&& str[i] != '{') && (str[i] && str[i] != '}') && (str[i]
			&& str[i] != '!') && (str[i] && str[i] != '.') && (str[i]
			&& str[i] != '='))
		return (true);
	return (false);
}
