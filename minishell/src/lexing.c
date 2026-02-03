/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:09:27 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/02/03 11:54:42 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lstfirst(t_token *lst)
{
	t_token	*cursor;

	cursor = lst;
	while (cursor != NULL)
	{
		if (cursor->previous == NULL)
			return (cursor);
		cursor = cursor->previous;
	}
	return (cursor);
}

t_token	*lstadd_back(t_token *lst, char *buffer, t_token_type type)
{
	t_token	*last;
	t_token	*curseur;

	last = malloc(sizeof(t_token));
	if (!last)
		return (NULL);
	last->var = ft_strdup(buffer);
	last->next = NULL;
	last->type = type;
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

void	printmini(t_token *mini)
{
	mini = lstfirst(mini);
	if (!mini)
	{
		printf("error\n");
		return ;
	}
	while (mini->next != NULL)
	{
		printf("value string : [%s]\n", mini->var);
		printf("type : [%d]\n", mini->type);
		mini = mini->next;
	}
	printf("valeur de fin : [%s]\n", mini->var);
	printf("type : [%d]\n", mini->type);
}

char	*add_char(char *buffer, char new)
{
	char	*temp;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(buffer);
	temp = malloc(sizeof(char *) * len + 2);
	while(buffer[i] != '\0')
	{
		temp[i] = buffer[i];
		i++;
	}
	temp[i] = new;
	i++;
	temp[i] = '\0';
	return (temp);
}

void	normal_state(char **buffer, char cara, t_state *state, t_token **mini_vars)
{
	if (cara >= 'a' && cara <= 'z')
			*buffer = add_char(*buffer, cara);
	if ((cara == ' ') || (cara >= 7 && cara <= 13))
	{
		if (*buffer[0] != '\0')
		{
			*mini_vars = lstadd_back(*mini_vars, *buffer, WORD);
			free(*buffer);
			*buffer = malloc(1);
			*buffer[0] = '\0';
		}
	}
	if (cara == '|')
	{
		if (*buffer[0] != '\0')
		{
			*mini_vars = lstadd_back(*mini_vars, *buffer, WORD);
			free(*buffer);
			*buffer = malloc(1);
			*buffer[0] = '\0';
		}
		*mini_vars = lstadd_back(*mini_vars, "|", PIPE);
		free(*buffer);
		*buffer = malloc(1);
		*buffer[0] = '\0';
	}
	if (cara == '"')
	{
		*state = IN_D_QUOTE;
	}
}

void	in_d_quote_state(char **buffer, char cara, t_state *state, t_token **mini_vars)
{
	(void)mini_vars;
	if (cara >= ' ' && cara <= '~')
	{
		*buffer = add_char(*buffer, cara);
	}
	if (cara == '"')
		*state = NORMAL;
}

t_token	*lexing(t_token *mini_vars, char *line)
{
	int		i;
	t_state	state;
	char	*buffer;

	i = 0;
	state = NORMAL;
	buffer = malloc(1);
	buffer[0] = '\0';
	while (line[i] != '\0')
	{
		if (state == NORMAL)
		{
			normal_state(&buffer, line[i], &state, &mini_vars);
		}
		if (state == IN_D_QUOTE)
		{
			in_d_quote_state(&buffer, line[i], &state, &mini_vars);
		}
		i++;
	}
	mini_vars = lstadd_back(mini_vars, buffer, WORD);
	return (mini_vars);
}
