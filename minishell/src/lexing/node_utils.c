/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:35:46 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/21 15:57:47 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_minidelone(t_sub_token *lst)
{
	if (!lst)
		return ;
	if (lst->var)
		free(lst->var);
	free(lst);
}

void	ft_miniclear(t_token **lst)
{
	t_token		*cursor;
	t_sub_token	*sub_cursor;
	t_sub_token	*sub_next;
	t_token		*next;

	if (!lst || !*lst)
		return ;
	cursor = *lst;
	while (cursor)
	{
		sub_cursor = cursor->sub_token;
		while (sub_cursor)
		{
			sub_next = sub_cursor->next;
			ft_minidelone(sub_cursor);
			sub_cursor = sub_next;
		}
		next = cursor->next;
		free(cursor);
		cursor = next;
	}
	*lst = NULL;
}

void	printmini(t_token **mini)
{
	t_token		*cursor;
	t_sub_token	*sub_cursor;
	t_sub_token	*sub_next;
	t_token		*next;
	int			i;

	if (!mini || !*mini)
		return ;
	cursor = *mini;
	i = 0;
	while (cursor)
	{
		printf("token %d [%d]\n", i, cursor->type);
		sub_cursor = cursor->sub_token;
		while (sub_cursor)
		{
			sub_next = sub_cursor->next;
			printf("	sub_token : [%s]\n", sub_cursor->var);
			printf("	quote : [%d]\n", sub_cursor->quote);
			sub_cursor = sub_next;
		}
		next = cursor->next;
		cursor = next;
		i++;
	}
}

void	add_char_2(char *buffer, char new, char *temp)
{
	int	i;

	i = 0;
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
}

char	*add_char(char *buffer, char new, t_state *state)
{
	char	*temp;
	int		len;

	if (!buffer)
		len = 0;
	else
		len = ft_strlen(buffer);
	temp = malloc(sizeof(char) * len + 2);
	if (!temp)
	{
		if (buffer)
			free(buffer);
		*state = ERROR;
		return (NULL);
	}
	add_char_2(buffer, new, temp);
	free(buffer);
	return (temp);
}
