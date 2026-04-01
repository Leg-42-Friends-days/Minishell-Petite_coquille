/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 18:28:27 by mickzhan          #+#    #+#             */
/*   Updated: 2026/04/01 14:47:50 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_new_string2(char *new_string, char *str, char *key, char *env)
{
	int	i;
	int	k;
	int	count;

	i = 0;
	k = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$' && count == 0)
		{
			i += ft_strlen(key) + 1;
			count++;
			copy_env(new_string, env, &k);
			continue ;
		}
		string_advance(new_string, str, &i, &k);
	}
	new_string[k] = '\0';
}

char	*check_new_string(char *str, char *key, char *env)
{
	int		env_len;
	char	*new_string;

	env_len = 0;
	if (env)
		env_len = ft_strlen(env);
	new_string = malloc(ft_strlen(str) + env_len - ft_strlen(key) + 1
			* sizeof(char));
	if (!new_string)
		return (free(str), NULL);
	check_new_string2(new_string, str, key, env);
	return (free(str), new_string);
}

char	*new_string2(char *new_str, int i, t_global *global)
{
	char	*key;
	char	*content;
	char	*tmp;

	key = check_key(new_str + i + 1);
	if (!key)
		return (free(new_str), NULL);
	if (new_str[i + 1] == '?')
		content = code_str(new_str + i + 1, global->error_code);
	else
		content = check_string(key, global->env);
	tmp = check_new_string(new_str, key, content);
	free_new_string(key, content);
	return (tmp);
}

char	*new_string(char *str, t_global *global)
{
	int		i;
	char	*new_str;
	int		len;

	i = 0;
	new_str = ft_strdup(str);
	if (!new_str)
		return (free(str), NULL);
	while (new_str[i])
	{
		if (check_dollar(new_str, i) == true)
		{
			len = new_string_len(new_str, i, global);
			new_str = new_string2(new_str, i, global);
			if (!new_str)
				return (free(str), NULL);
			i += len;
		}
		else
			i++;
	}
	return (free(str), new_str);
}

int	new_string_len(char *new_str, int i, t_global *global)
{
	char	*key;
	char	*content;
	int		len;

	len = 0;
	key = check_key(new_str + i + 1);
	if (!key)
		return (0);
	if (new_str[i + 1] == '?')
		content = code_str(new_str + i + 1, global->error_code);
	else
		content = check_string(key, global->env);
	if (content)
		len = ft_strlen(content);
	else
		len = 0;
	free(key);
	free(content);
	return (len);
}
