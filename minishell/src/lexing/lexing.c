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

#include "lexer.h"

void	buffer_full(t_token **mini_vars, char **buffer)
{
	t_token	*current;
	
	if (!*buffer)
		return ;
	if (*buffer && (*buffer[0] != '<' && *buffer[0] != '>'))
	{
		if (!(*mini_vars))
				lstadd_back(addnode(WORD), mini_vars);
		lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars);
		free(*buffer);
		*buffer = NULL;
	}
	else if (*buffer && *buffer[0] == '<')
	{
		lstadd_back(addnode(INFILE), mini_vars);
		lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars);
		free(*buffer);
		*buffer = NULL;
		if (*mini_vars)
		{
			current = find_last(mini_vars);
			current->token_state = 0;
		}
	}
	else if (*buffer && *buffer[0] == '>')
	{
		lstadd_back(addnode(OUTFILE), mini_vars);
		lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars);
		free(*buffer);
		*buffer = NULL;
		if (*mini_vars)
		{
			current = find_last(mini_vars);
			current->token_state = 0;
		}
	}
}

void	normal_state(char **buffer, char cara, t_state *state, t_token **mini_vars)
{
	t_token	*current;

	if ((cara == ' ') || (cara >= 7 && cara <= 13))
	{
		buffer_full(mini_vars, buffer);
		if (*mini_vars)
		{
			current = find_last(mini_vars);
			current->token_state = 0;
		}
	}
	else if (cara == '|')
	{
		buffer_full(mini_vars, buffer);
		lstadd_back(addnode(PIPE), mini_vars);
		lstadd_sub_back(add_subnode("|", NONE), mini_vars);
		if (*mini_vars)
		{
			current = find_last(mini_vars);
			current->token_state = 0;
		}
	}
	else if (cara == '<')
	{
		if (*buffer && (*buffer[0] != '<' && *buffer[0] != '>'))
		{
			lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars);
			free(*buffer);
			*buffer = NULL;
			*buffer = add_char(*buffer, cara);
		}
		else if (*buffer && *buffer[0] == '<')
		{
			lstadd_back(addnode(HEREDOC), mini_vars);
			lstadd_sub_back(add_subnode("<<", NONE), mini_vars);
			free(*buffer);
			*buffer = NULL;
		}
		else if (*buffer && *buffer[0] == '>')
		{
			lstadd_back(addnode(OUTFILE), mini_vars);
			lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars);
			free(*buffer);
			*buffer = NULL;
			*buffer = add_char(*buffer, cara);
		}
		else
			*buffer = add_char(*buffer, cara);
		if (*mini_vars)
		{
			current = find_last(mini_vars);
			current->token_state = 0;
		}
	}
	else if (cara == '>')
	{
		if (*buffer && (*buffer[0] != '>' && *buffer[0] != '<'))
		{
			lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars);
			free(*buffer);
			*buffer = NULL;
			*buffer = add_char(*buffer, cara);
		}
		else if (*buffer && *buffer[0] == '>')
		{
			lstadd_back(addnode(APPEND), mini_vars);
			lstadd_sub_back(add_subnode(">>", NONE), mini_vars);
			free(*buffer);
			*buffer = NULL;
		}
		else if (*buffer && *buffer[0] == '<')
		{
			lstadd_back(addnode(INFILE), mini_vars);
			lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars);
			free(*buffer);
			*buffer = NULL;
			*buffer = add_char(*buffer, cara);
		}
		else 
			*buffer = add_char(*buffer, cara);
		if (*mini_vars)
		{
			current = find_last(mini_vars);
			current->token_state = 0;
		}
	}
	else if (cara == 39)
	{
		buffer_full(mini_vars, buffer);
		*state = IN_S_QUOTE;
	}
	else if (cara == '"')
	{
		buffer_full(mini_vars, buffer);
		*state = IN_D_QUOTE;
	}
	else if (cara >= '!' && cara <= '~')
	{
		if (!*mini_vars)
			lstadd_back(addnode(WORD), mini_vars);
		if (*buffer && *buffer[0] == '>')
		{
			lstadd_back(addnode(INFILE), mini_vars);
			lstadd_sub_back(add_subnode(">", NONE), mini_vars);
			free(*buffer);
			*buffer = NULL;
			current = find_last(mini_vars);
			current->token_state = 0;
		}
		else if (*buffer && *buffer[0] == '<')
		{
			lstadd_back(addnode(OUTFILE), mini_vars);
			lstadd_sub_back(add_subnode(">", NONE), mini_vars);
			free(*buffer);
			*buffer = NULL;
			current = find_last(mini_vars);
			current->token_state = 0;
		}
		current = find_last(mini_vars);
		if (current->token_state == 0)
			lstadd_back(addnode(WORD), mini_vars);
		*buffer = add_char(*buffer, cara);
	}
}

t_token	*lexing(t_token **mini_vars, char *line)
{
	int		i;
	t_state	state;
	char	*buffer;
	t_token	*current;

	i = 0;
	state = NORMAL;
	buffer = NULL;
	while (line[i] != '\0' && line[i] == ' ')
	{
		i++;
	}
	if (line[i] == '\0')
		return (NULL);
	while (line[i] != '\0')
	{
		if (state == NORMAL)
			normal_state(&buffer, line[i], &state, mini_vars);
		else if (state == IN_D_QUOTE)
			in_d_quote_state(&buffer, line[i], &state, mini_vars);
		else if (state == IN_S_QUOTE)
			in_s_quote_state(&buffer, line[i], &state, mini_vars);
		i++;
	}
	if (buffer)
	{
		if (buffer[0] == '<')
		{
			lstadd_back(addnode(INFILE), mini_vars);
			lstadd_sub_back(add_subnode(buffer, NONE), mini_vars);
		}
		else if (buffer[0] == '>')
		{
			lstadd_back(addnode(OUTFILE), mini_vars);
			lstadd_sub_back(add_subnode(buffer, NONE), mini_vars);
		}
		else if (buffer[0] != '|')
		{
			if (!(*mini_vars))
				lstadd_back(addnode(WORD), mini_vars);
			current = find_last(mini_vars);
			if (current->token_state == 0)
				lstadd_back(addnode(WORD), mini_vars);
			lstadd_sub_back(add_subnode(buffer, NONE), mini_vars);
		}
		free(buffer);
	}
	if (!(*mini_vars))
		lstadd_back(addnode(WORD), mini_vars);
	return (*mini_vars);
}
