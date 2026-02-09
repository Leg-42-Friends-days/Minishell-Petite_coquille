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

t_token	*addnode(t_token_type type)
{
	t_token	*add_node;

	add_node = malloc(sizeof(t_token));
	if (!add_node)
		return (NULL);
	add_node->token_state = 1;
	add_node->sub_token = NULL;
	add_node->type = type;
	add_node->next = NULL;
	add_node->prev = NULL;
	return (add_node);
}

t_sub_token *add_subnode(char *buffer, t_quote quote)
{
	t_sub_token	*add_sub_node;

	add_sub_node = malloc(sizeof(t_sub_token));
	if (!add_sub_node)
		return (NULL);
	add_sub_node->var = ft_strdup(buffer);
	add_sub_node->quote = quote;
	add_sub_node->next = NULL;
	add_sub_node->prev = NULL;
	return (add_sub_node);
}

t_token	*find_last(t_token **lst)
{
	t_token	*last;

	if (!lst)
		return (NULL);
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	lstadd_back(t_token *new, t_token **lst)
{
	t_token	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->prev = last;
	new->next = NULL;
}

void	lstadd_sub_back(t_sub_token *new, t_token **lst)
{
	t_sub_token	*last;
	t_token		*current;

	if (!lst || !new)
		return ;
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	if (!current->sub_token)
	{
		current->sub_token = new;
		return ;
	}
	last = current->sub_token;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->prev = last;
	new->next = NULL;
}

void	printmini(t_token **mini)
{
	int	i;

	i = 1;
	if (!*mini)
	{
		printf("error\n");
		return ;
	}
	while ((*mini)->next != NULL)
	{
		printf("token %d [%d]\n", i, (*mini)->type);
		while ((*mini)->sub_token->next != NULL)
		{
			printf("	sub_token : [%s]\n", (*mini)->sub_token->var);
			printf("	quote : [%d]\n", (*mini)->sub_token->quote);
			(*mini)->sub_token = (*mini)->sub_token->next;
		}
		if((*mini)->sub_token->var)
		{
		printf("	sub_token : [%s]\n", (*mini)->sub_token->var);
		printf("	quote : [%d]\n", (*mini)->sub_token->quote);
		*mini = (*mini)->next;
		}
		i ++;
	}
	printf("token %d [%d]\n", i, (*mini)->type);
	while ((*mini)->sub_token->next != NULL)
	{
		printf("	sub_token : [%s]\n", (*mini)->sub_token->var);
		printf("	quote : [%d]\n", (*mini)->sub_token->quote);
		(*mini)->sub_token = (*mini)->sub_token->next;
	}
	if ((*mini)->sub_token->var)
	{ls
		printf("	sub_token : [%s]\n", (*mini)->sub_token->var);
		printf("	quote : [%d]\n", (*mini)->sub_token->quote);
	}
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
	temp = malloc(sizeof(char) * len + 2);
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
	free(buffer);
	return (temp);
}

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

void	in_d_quote_state(char **buffer, char cara, t_state *state, t_token **mini_vars)
{
	if (*mini_vars)
		{
			if (find_last(mini_vars)->token_state == 0)
				lstadd_back(addnode(WORD), mini_vars);
		}
	if (cara == '"')
	{
		if (!(*mini_vars))
			lstadd_back(addnode(WORD), mini_vars);
		if (!*buffer)
			lstadd_sub_back(add_subnode("", DOUBLE), mini_vars);
		if (*buffer)
		{
			lstadd_sub_back(add_subnode(*buffer, DOUBLE), mini_vars);
			free(*buffer);
			*buffer = NULL;
		}
		*state = NORMAL;
	}
	else if (cara >= ' ' && cara <= '~')
		*buffer = add_char(*buffer, cara);
}

void	in_s_quote_state(char **buffer, char cara, t_state *state, t_token **mini_vars)
{
	if (*mini_vars)
		{
			if (find_last(mini_vars)->token_state == 0)
				lstadd_back(addnode(WORD), mini_vars);
		}
	if (cara == 39)
	{
		if (!(*mini_vars))
			lstadd_back(addnode(WORD), mini_vars);
		if (!*buffer)
			lstadd_sub_back(add_subnode("", SINGLE), mini_vars);
		if (*buffer)
		{
			lstadd_sub_back(add_subnode(*buffer, SINGLE), mini_vars);
			free(*buffer);
			*buffer = NULL;
		}
		*state = NORMAL;
	}
	else if (cara >= ' ' && cara <= '~')
		*buffer = add_char(*buffer, cara);
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
