/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cara_types_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:48:36 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/21 15:59:47 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	meta_cara_3(char **buffer, char cara, t_token **mini, t_state *s)
{
	if (cara == '|')
	{
		lstadd_back(addnode(OR), mini, s);
		lstadd_sub_back(add_subnode("||", NONE), mini, s);
	}
	if (cara == '&')
	{
		lstadd_back(addnode(AND), mini, s);
		lstadd_sub_back(add_subnode("&&", NONE), mini, s);
	}
	free(*buffer);
	*buffer = NULL;
}

void	meta_cara_2(char **buffer, char cara, t_token **mini, t_state *s)
{
	if (!(*mini))
		lstadd_back(addnode(WORD), mini, s);
	lstadd_sub_back(add_subnode(*buffer, NONE), mini, s);
	free(*buffer);
	*buffer = NULL;
	*buffer = add_char(*buffer, cara, s);
}

void	meta_cara(char **buffer, char cara, t_token **mini, t_state *state)
{
	if (*buffer && (*buffer[0] != '|' && *buffer[0] != '&'))
		meta_cara_2(buffer, cara, mini, state);
	else if (*buffer && (*buffer[0] == '&' && cara == '|'))
		meta_cara_2(buffer, cara, mini, state);
	else if (*buffer && (*buffer[0] == '|' && cara == '&'))
	{
		if (!(*mini))
			lstadd_back(addnode(PIPE), mini, state);
		lstadd_sub_back(add_subnode(*buffer, NONE), mini, state);
		free(*buffer);
		*buffer = NULL;
		*buffer = add_char(*buffer, cara, state);
	}
	else if (*buffer && *buffer[0] == cara)
		meta_cara_3(buffer, cara, mini, state);
	else
		*buffer = add_char(*buffer, cara, state);
	close_token(mini);
}

void	other_cara_if(char **buffer, t_token **mini_vars, t_state *state)
{
	if (*buffer[0] == '<')
		lstadd_back(addnode(INFILE), mini_vars, state);
	if (*buffer[0] == '>')
		lstadd_back(addnode(OUTFILE), mini_vars, state);
	if (*buffer[0] == '|')
		lstadd_back(addnode(PIPE), mini_vars, state);
	if (*buffer[0] == '&')
		lstadd_back(addnode(WORD), mini_vars, state);
	if (*buffer[0] == '(')
		lstadd_back(addnode(L_PAR), mini_vars, state);
	if (*buffer[0] == ')')
		lstadd_back(addnode(R_PAR), mini_vars, state);
}

void	other_cara(char **buffer, char cara, t_token **mini, t_state *s)
{
	t_token	*current;

	if (*buffer && (*buffer[0] == '>' || *buffer[0] == '<' || *buffer[0] == '|'
			|| *buffer[0] == '&' || *buffer[0] == '(' || *buffer[0] == ')'))
	{
		other_cara_if(buffer, mini, s);
		lstadd_sub_back(add_subnode(*buffer, NONE), mini, s);
		free(*buffer);
		*buffer = NULL;
		close_token(mini);
	}
	if (!*mini)
		lstadd_back(addnode(WORD), mini, s);
	current = find_last(mini);
	if (current->token_state == 0)
		lstadd_back(addnode(WORD), mini, s);
	*buffer = add_char(*buffer, cara, s);
}
