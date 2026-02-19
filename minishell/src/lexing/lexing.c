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

void	normal_state(char **buffer, char cara, t_state *state, t_token **mini)
{
	if ((cara == ' ') || (cara >= 7 && cara <= 13))
	{
		buffer_full(mini, buffer, state);
		close_token(mini);
	}
	else if (cara == '|' || cara == '&')
		meta_cara(buffer, cara, mini, state);
	else if (cara == '(' || cara == ')')
		brackets(buffer, cara, mini, state);
	else if (cara == '<' || cara == '>')
		angles_brackets(buffer, cara, mini, state);
	else if (cara == 39 || cara == '"')
		quotes(buffer, cara, mini, state);
	else if (cara >= '!' && cara <= '~')
		other_cara(buffer, cara, mini, state);
}

int	cara_iteration(char *line, char **buffer, t_token **mini_vars, t_state *state)
{
	int		i;

	i = 0;
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (1);
	while (line[i] != '\0')
	{
		if (*state == NORMAL)
			normal_state(buffer, line[i], state, mini_vars);
		else if (*state == IN_D_QUOTE)
			in_d_quote_state(buffer, line[i], state, mini_vars);
		else if (*state == IN_S_QUOTE)
			in_s_quote_state(buffer, line[i], state, mini_vars);
		if (*state == ERROR)
			return (0);
		i++;
	}
	return (0);
}

void	last_token(char **buffer, t_token **mini_vars, t_state *state)
{
	t_token	*current;

	if (*buffer && (*buffer[0] == '<' || *buffer[0] == '>' || *buffer[0] == '|'
		|| *buffer[0] == '(' || *buffer[0] == ')'))
	{
		if (*buffer[0] == '<')
			lstadd_back(addnode(INFILE), mini_vars, state);
		else if (*buffer[0] == '>')
			lstadd_back(addnode(OUTFILE), mini_vars, state);
		else if (*buffer[0] == '|')
			lstadd_back(addnode(PIPE), mini_vars, state);
		else if (*buffer[0] == '(')
			lstadd_back(addnode(L_PAR), mini_vars, state);
		else if (*buffer[0] == ')')
			lstadd_back(addnode(R_PAR), mini_vars, state);
		lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars, state);
	}
	else if (*buffer)
	{
		current = find_last(mini_vars);
		if (current->token_state == 0)
			lstadd_back(addnode(WORD), mini_vars, state);
		lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars, state);
	}
	free(*buffer);
}

t_token	*lexing(t_token **mini_vars, char *line)
{
	char	*buffer;
	t_state	state;

	state = NORMAL;
	buffer = NULL;
	if ((cara_iteration(line, &buffer, mini_vars, &state)) == 1)
		return (NULL);
	if (state == 1 || state == 2)
	{
		ft_miniclear(mini_vars);
		printf("minishell: unclosed quote\n");
		return (NULL);
	}
	if (state == ERROR)
	{
		ft_miniclear(mini_vars);
		//if(buffer)
		//	free(buffer);
		printf("minishell: cannot allocate memory\n");
		return (NULL);
	}
	if (buffer)
		last_token(&buffer, mini_vars, &state);
	if (state == ERROR)
	{
		ft_miniclear(mini_vars);
		//if (buffer)
		//	free(buffer);
		printf("minishell: cannot allocate memory\n");
		return (NULL);
	}
	if (!(*mini_vars))
		lstadd_back(addnode(WORD), mini_vars, &state);
	return (*mini_vars);
}
