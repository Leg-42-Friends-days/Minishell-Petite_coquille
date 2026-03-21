/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cara_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:11:16 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/21 15:50:10 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	angles_brackets_2(char **buf, char cara, t_token **mini, t_state *state)
{
	if (cara == '<')
	{
		lstadd_back(addnode(HEREDOC), mini, state);
		lstadd_sub_back(add_subnode("<<", NONE), mini, state);
	}
	if (cara == '>')
	{
		lstadd_back(addnode(APPEND), mini, state);
		lstadd_sub_back(add_subnode(">>", NONE), mini, state);
	}
	free(*buf);
	*buf = NULL;
}

void	angle_bracket(char **buffer, char cara, t_token **mini, t_state *state)
{
	if (*buffer && (*buffer[0] != '<' && *buffer[0] != '>'))
	{
		if (!(*mini))
			lstadd_back(addnode(WORD), mini, state);
		lstadd_sub_back(add_subnode(*buffer, NONE), mini, state);
		free(*buffer);
		*buffer = NULL;
		*buffer = add_char(*buffer, cara, state);
	}
	else if (*buffer && *buffer[0] == cara)
		angles_brackets_2(buffer, cara, mini, state);
	else if (*buffer && (*buffer[0] == '>' || *buffer[0] == '<'))
	{
		if (*buffer[0] == '<')
			lstadd_back(addnode(INFILE), mini, state);
		if (*buffer[0] == '>')
			lstadd_back(addnode(OUTFILE), mini, state);
		lstadd_sub_back(add_subnode(*buffer, NONE), mini, state);
		free(*buffer);
		*buffer = NULL;
		*buffer = add_char(*buffer, cara, state);
	}
	else
		*buffer = add_char(*buffer, cara, state);
	close_token(mini);
}

void	quotes(char **buffer, char cara, t_token **mini_vars, t_state *state)
{
	if (cara == 39)
	{
		buffer_full(mini_vars, buffer, state);
		*state = IN_S_QUOTE;
	}
	else if (cara == '"')
	{
		buffer_full(mini_vars, buffer, state);
		*state = IN_D_QUOTE;
	}
}

void	brackets(char **buffer, char cara, t_token **mini_vars, t_state *state)
{
	buffer_full(mini_vars, buffer, state);
	if (cara == '(' || cara == ')')
	{
		if (cara == '(')
		{
			lstadd_back(addnode(L_PAR), mini_vars, state);
			lstadd_sub_back(add_subnode("(", NONE), mini_vars, state);
		}
		if (cara == ')')
		{
			lstadd_back(addnode(R_PAR), mini_vars, state);
			lstadd_sub_back(add_subnode(")", NONE), mini_vars, state);
		}
	}
	close_token(mini_vars);
}
