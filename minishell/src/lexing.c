/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:09:27 by ibrouin-          #+#    #+#             */
/*																			*/
/*   Updated: 2026/02/03 16:44:07 by ibrouin-         ###   ########.fr       */
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

	if (!buffer)
		len = 0;
	else
		len = ft_strlen(buffer);
	i = 0;
	temp = malloc(sizeof(char *) * len + 2);
	if (!temp)
		return(NULL);
	if (buffer)
	{
		while(buffer[i] != '\0')
		{
			temp[i] = buffer[i]; 
			i++;
		}
	}
	temp[i] = new;
	i++;
	temp[i] = '\0';
	return (temp);
}

void	buffer_full(t_token **mini_vars, char **buffer)
{
	if (*buffer && (*buffer[0] != '<' && *buffer[0] != '>'))
	{
		*mini_vars = lstadd_back(*mini_vars, *buffer, WORD);
		free(*buffer);
		*buffer = NULL;
	}
	if (*buffer && *buffer[0] == '<')
	{
		*mini_vars = lstadd_back(*mini_vars, "<", INFILE);
		free(*buffer);
		*buffer = NULL;
	}
	if (*buffer && *buffer[0] == '>')
	{
		*mini_vars = lstadd_back(*mini_vars, ">", OUTFILE);
		free(*buffer);
		*buffer = NULL;
	}
}

void	normal_state(char **buffer, char cara, t_state *state, t_token **mini_vars)
{
	if ((cara == ' ') || (cara >= 7 && cara <= 13))
		buffer_full(mini_vars, buffer);
	else if (cara == '|')
	{
		buffer_full(mini_vars, buffer);
		*mini_vars = lstadd_back(*mini_vars, "|", PIPE);
	}
	else if (cara == '<')
	{
		if (*buffer && *buffer[0] != '<')
		{
			*mini_vars = lstadd_back(*mini_vars, *buffer, WORD);
			free(*buffer);
			*buffer = NULL;
		}
		if (*buffer && *buffer[0] == '<')
		{
			*mini_vars = lstadd_back(*mini_vars, "<<", HEREDOC);
			free(*buffer);
			*buffer = NULL;
		}
		else
			*buffer = add_char(*buffer, cara);
	}
	else if (cara == '>')
	{
		if (*buffer && *buffer[0] != '>')
		{
			*mini_vars = lstadd_back(*mini_vars, *buffer, WORD);
			free(*buffer);
			*buffer = NULL;
		}
		if (*buffer && *buffer[0] == '>')
		{
			*mini_vars = lstadd_back(*mini_vars, ">>", APPEND);
			free(*buffer);
			*buffer = NULL;
		}
		else
			*buffer = add_char(*buffer, cara);
	}
	else if (cara == 39)
		*state = IN_S_QUOTE;
	else if (cara == '"')
		*state = IN_D_QUOTE;
	else if (cara >= '!' && cara <= '~')
		*buffer = add_char(*buffer, cara);
}

void	in_d_quote_state(char **buffer, char cara, t_state *state, t_token **mini_vars)
{
	(void)mini_vars;
	if (cara == '"')
		*state = NORMAL;
	else if (cara >= ' ' && cara <= '~')
	{
		*buffer = add_char(*buffer, cara);
	}
}

void	in_s_quote_state(char **buffer, char cara, t_state *state, t_token **mini_vars)
{
	(void)mini_vars;
	if (cara == 39)
		*state = NORMAL;
	else if (cara >= ' ' && cara <= '~')
	{
		*buffer = add_char(*buffer, cara);
	}
}

t_token	*lexing(t_token *mini_vars, char *line)
{
	int		i;
	t_state	state;
	char	*buffer;

	i = 0;
	state = NORMAL;
	buffer = NULL;
	while (line[i] != '\0')
	{
		if (state == NORMAL)
			normal_state(&buffer, line[i], &state, &mini_vars);
		else if (state == IN_D_QUOTE)
			in_d_quote_state(&buffer, line[i], &state, &mini_vars);
		else if (state == IN_S_QUOTE)
			in_s_quote_state(&buffer, line[i], &state, &mini_vars);
		i++;
	}
	if (buffer)
		mini_vars = lstadd_back(mini_vars, buffer, WORD);
	return (mini_vars);
}
