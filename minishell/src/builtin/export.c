/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:20:36 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/26 12:15:02 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*lstadd_back_exp(t_env *lst, char *key, char *value)
{
	t_env	*last;
	t_env	*curseur;

	if (key == NULL || value == NULL)
		return (NULL);
	last = malloc(sizeof(t_env));
	if (!last)
		return (NULL);
	last->key = key;
	last->content = value;
	last->free_export = true;
	last->next = NULL;
	if (lst == NULL)
	{
		last->previous = NULL;
		return (last);
	}
	curseur = lst;
	while (curseur->next != NULL)
		curseur = curseur->next;
	curseur->next = last;
	last->previous = curseur;
	return (last);
}

char	*get_content(char *test)
{
	int		i;
	int		j;
	char	*str;

	i = find_letter(test, '=');
	j = 0;
	while (test[i])
	{
		j++;
		i++;
	}
	str = malloc(sizeof(char) * (j + 1));
	i = find_letter(test, '=') + 1;
	j = 0;
	while (test[i])
	{
		str[j] = test[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}

bool	list_of_error(char key)
{
	if ((key && key != '!') && (key && key != '@') && (key && key != '$')
		&& (key && key != '%') && (key && key != '^') && (key && key != '*')
		&& (key && key != '~') && (key && key != '[') && (key && key != ']')
		&& (key && key != '/') && (key && key != '.') && (key && key != ',')
		&& (key && key != '{') && (key && key != '}') && (key) && (key
			&& key != '#') && (key && key != '?'))
		return (true);
	return (false);
}

bool	not_exportable(char *str)
{
	int		i;
	char	*key;

	i = 0;
	if (str[i] == '\0')
	{
		ft_printf(2, "Minishell: export: `': not a valid identifier\n");
		return (false);
	}
	key = get_key(str);
	while (key[i])
	{
		if (key[0] >= '0' && key[0] <= '9')
			return (free(key), true);
		else if (list_of_error(key[i]) == true)
			i++;
		else
			return (free(key), true);
	}
	free(key);
	return (false);
}

bool	get_equal(char *str, int *error)
{
	int	i;

	i = 0;
	if (str[i] == '=')
	{
		ft_printf(2, "Minishell: export: `%s': not a valid identifier\n", str);
		*error = 1;
		return (false);
	}
	if (not_exportable(str) == true)
	{
		ft_printf(2, "Minishell: export: `%s': not a valid identifier\n", str);
		*error = 1;
		return (false);
	}
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}
