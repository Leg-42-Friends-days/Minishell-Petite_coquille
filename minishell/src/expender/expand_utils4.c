/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 18:25:04 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/31 18:25:47 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*star_str(char *str)
{
	int		i;
	char	*key;

	i = 0;
	if (str[i] == '*')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	if (str[i] == '*')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*code_str(char *str, int error_code)
{
	char	*key;

	key = NULL;
	if (str && str[0] == '?')
		key = ft_itoa(error_code);
	return (key);
}

char	*check_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
		return (key = number_str(str));
	if (str[i] == '*')
		return (key = star_str(str));
	if (str[i] == '?')
		return (key = ft_strdup("?"));
	while (check_condition_key(str, i) == true)
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (check_condition_key(str, i) == true)
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

void	copy_env(char *new_string, char *env, int *k)
{
	int	j;

	j = 0;
	while (env && env[j])
	{
		new_string[*k] = env[j];
		(*k)++;
		j++;
	}
}

void	string_advance(char *new_string, char *str, int *i, int *k)
{
	new_string[*k] = str[*i];
	(*i)++;
	(*k)++;
}
