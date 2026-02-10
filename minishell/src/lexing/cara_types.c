/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cara_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:11:16 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/02/10 18:22:52 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	angles_brackets_2(char **buffer, char cara, t_token **mini_vars)
{
	if (cara == '<')
	{
		lstadd_back(addnode(HEREDOC), mini_vars);
		lstadd_sub_back(add_subnode("<<", NONE), mini_vars);
	}
	if (cara == '>')
	{
		lstadd_back(addnode(APPEND), mini_vars);
		lstadd_sub_back(add_subnode(">>", NONE), mini_vars);
	}
	free(*buffer);
	*buffer = NULL;
}

void	angles_brackets(char **buffer, char cara, t_token **mini_vars)
{
	if (*buffer && (*buffer[0] != '<' && *buffer[0] != '>'))
	{
		if (!(*mini_vars))
			lstadd_back(addnode(WORD), mini_vars);
		lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars);
		free(*buffer);
		*buffer = NULL;
		*buffer = add_char(*buffer, cara);
	}
	else if (*buffer && *buffer[0] == cara)
		angles_brackets_2(buffer, cara, mini_vars);
	else if (*buffer && (*buffer[0] == '>' || *buffer[0] == '<'))
	{
		if (*buffer[0] == '<')
			lstadd_back(addnode(INFILE), mini_vars);
		if (*buffer[0] == '>')
			lstadd_back(addnode(OUTFILE), mini_vars);
		lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars);
		free(*buffer);
		*buffer = NULL;
		*buffer = add_char(*buffer, cara);
	}
	else
		*buffer = add_char(*buffer, cara);
	close_token(mini_vars);
}

void	quotes(char **buffer, char cara, t_token **mini_vars, t_state *state)
{
	if (cara == 39)
	{
		buffer_full(mini_vars, buffer);
		*state = IN_S_QUOTE;
	}
	else if (cara == '"')
	{
		buffer_full(mini_vars, buffer);
		*state = IN_D_QUOTE;
	}
}

void	meta_cara(char **buffer, char cara, t_token **mini_vars)
{
	if (*buffer && (*buffer[0] != '|' || *buffer[0] !=))
	{
		if (!(*mini_vars))
			lstadd_back(addnode(WORD), mini_vars);
		lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars);
		free(*buffer);
		*buffer = NULL;
		*buffer = add_char(*buffer, cara);
	}
	if 
	else if (*buffer && *buffer[0] == cara)
	{
		if (cara == '|')
		{
			lstadd_back(addnode(OR), mini_vars);
			lstadd_sub_back(add_subnode("||", NONE), mini_vars);
		}
		free(*buffer);
		*buffer = NULL;
	}
	else
		*buffer = add_char(*buffer, cara);
	close_token(mini_vars);
}

void	other_cara(char **buffer, char cara, t_token **mini_vars)
{
	t_token	*current;

	if (*buffer && (*buffer[0] == '>' || *buffer[0] == '<' || *buffer[0] == '|' ))
	{
		if (*buffer[0] == '<')
			lstadd_back(addnode(INFILE), mini_vars);
		if (*buffer[0] == '>')
			lstadd_back(addnode(OUTFILE), mini_vars);
		if (*buffer[0] == '|')
			lstadd_back(addnode(PIPE), mini_vars);
		lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars);
		free(*buffer);
		*buffer = NULL;
		close_token(mini_vars);
	}
	if (!*mini_vars)
		lstadd_back(addnode(WORD), mini_vars);
	current = find_last(mini_vars);
	if (current->token_state == 0)
		lstadd_back(addnode(WORD), mini_vars);
	*buffer = add_char(*buffer, cara);
}
