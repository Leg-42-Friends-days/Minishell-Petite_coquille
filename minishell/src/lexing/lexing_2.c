/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:30:32 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/02/09 16:39:47 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*add_char(char *buffer, char new)
{
	char	*temp;
	int		len;
	int		i;

	if (!buffer)
		len = 0;
	else
		len = ft_strlen(buffer);
	i = 0;
	temp = malloc(sizeof(char) * len + 2);
	if (!temp)
		return (NULL);
	if (buffer)
	{
		while (buffer[i] != '\0')
		{
			temp[i] = buffer[i];
			i++;
		}
	}
	temp[i] = new;
	i++;
	temp[i] = '\0';
	free(buffer);
	return (temp);
}

void	in_d_quote_state(char **buf, char c, t_state *st, t_token **mini)
{
	if (*mini)
	{
		if (find_last(mini)->token_state == 0)
			lstadd_back(addnode(WORD), mini);
	}
	if (c == '"')
	{
		if (!(*mini))
			lstadd_back(addnode(WORD), mini);
		if (!*buf)
			lstadd_sub_back(add_subnode("", DOUBLE), mini);
		if (*buf)
		{
			lstadd_sub_back(add_subnode(*buf, DOUBLE), mini);
			free(*buf);
			*buf = NULL;
		}
		*st = NORMAL;
	}
	else if (c >= ' ' && c <= '~')
		*buf = add_char(*buf, c);
}

void	in_s_quote_state(char **buf, char c, t_state *st, t_token **mini)
{
	if (*mini)
	{
		if (find_last(mini)->token_state == 0)
			lstadd_back(addnode(WORD), mini);
	}
	if (c == 39)
	{
		if (!(*mini))
			lstadd_back(addnode(WORD), mini);
		if (!*buf)
			lstadd_sub_back(add_subnode("", SINGLE), mini);
		if (*buf)
		{
			lstadd_sub_back(add_subnode(*buf, SINGLE), mini);
			free(*buf);
			*buf = NULL;
		}
		*st = NORMAL;
	}
	else if (c >= ' ' && c <= '~')
		*buf = add_char(*buf, c);
}
