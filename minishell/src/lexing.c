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

t_token	*addnode(char *buffer, t_token_type type)
{
	t_token	*add_node;

	add_node = malloc(sizeof(t_token));
	if (!add_node)
		return (NULL);
	add_node->var = ft_strdup(buffer);
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
	if (!*mini)
	{
		printf("error\n");
		return ;
	}
	while ((*mini)->next != NULL)
	{
		printf("value string : [%s]\n", (*mini)->var);
		printf("type : [%d]\n", (*mini)->type);
		while ((*mini)->sub_token->next != NULL)
		{
			printf("sub_token : [%s]\n", (*mini)->sub_token->var);
			printf("quote : [%d]\n", (*mini)->sub_token->quote);
			(*mini)->sub_token = (*mini)->sub_token->next;
		}
		printf("sub_token : [%s]\n", (*mini)->sub_token->var);
		printf("quote : [%d]\n", (*mini)->sub_token->quote);
		*mini = (*mini)->next;
	}
	printf("valeur de fin : [%s]\n", (*mini)->var);
	printf("type : [%d]\n", (*mini)->type);
	while ((*mini)->sub_token->next != NULL)
	{
		printf("sub_token : [%s]\n", (*mini)->sub_token->var);
		printf("quote : [%d]\n", (*mini)->sub_token->quote);
		(*mini)->sub_token = (*mini)->sub_token->next;
	}
	printf("sub_token : [%s]\n", (*mini)->sub_token->var);
	printf("quote : [%d]\n", (*mini)->sub_token->quote);
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
	if (*buffer && (*buffer[0] != '<' && *buffer[0] != '>'))
	{
		lstadd_back(addnode(*buffer, WORD), mini_vars);
		lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars);
		free(*buffer);
		*buffer = NULL;
	}
	else if (*buffer && *buffer[0] == '<')
	{
		lstadd_back(addnode("<", INFILE), mini_vars);
		lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars);
		free(*buffer);
		*buffer = NULL;
	}
	else if (*buffer && *buffer[0] == '>')
	{
		lstadd_back(addnode(">", OUTFILE), mini_vars);
		lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars);
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
		*buffer = add_char(*buffer, cara);
		lstadd_back(addnode(*buffer, PIPE), mini_vars);
		lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars);
	}
	else if (cara == '<')
	{
		if (*buffer && *buffer[0] != '<')
		{
			lstadd_back(addnode(*buffer, WORD), mini_vars);
			lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars);
			free(*buffer);
			*buffer = NULL;
		}
		if (*buffer && *buffer[0] == '<')
		{
			lstadd_back(addnode("<<", HEREDOC), mini_vars);
			lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars);
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
			lstadd_back(addnode(*buffer, WORD), mini_vars);
			lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars);
			free(*buffer);
			*buffer = NULL;
		}
		if (*buffer && *buffer[0] == '>')
		{
			lstadd_back(addnode(">>", APPEND), mini_vars);
			lstadd_sub_back(add_subnode(*buffer, NONE), mini_vars);
			free(*buffer);
			*buffer = NULL;
		}
		else
			*buffer = add_char(*buffer, cara);
	}
	else if (cara == 39)
	{
		buffer_full(mini_vars, buffer);
		if (!*buffer)
			lstadd_back(addnode(" ", WORD), mini_vars);
		*state = IN_S_QUOTE;
	}
	else if (cara == '"')
	{
		buffer_full(mini_vars, buffer);
		if(!*buffer)
			lstadd_back(addnode(" ", WORD), mini_vars);
		*state = IN_D_QUOTE;
	}
	else if (cara >= '!' && cara <= '~')
		*buffer = add_char(*buffer, cara);
}

void	in_d_quote_state(char **buffer, char cara, t_state *state, t_token **mini_vars)
{
	/* if (*buffer)
	{
		lstadd_back(addnode(*buffer, WORD), mini_vars);
		lstadd_sub_back(add_subnode(*buffer, DOUBLE), mini_vars);
		free(*buffer);
		*buffer = NULL;
	} */
	//*buffer = add_char(*buffer, cara);
	if (cara == 39)
	{
		if (*buffer)
		{
			if (!(*mini_vars))
				lstadd_back(addnode(*buffer, WORD), mini_vars);
			lstadd_sub_back(add_subnode(*buffer, DOUBLE), mini_vars);
			free(*buffer);
			*buffer = NULL;
		}
		//*state = IN_S_QUOTE;
	}
	else if (cara == '"')
	{
		if (*buffer)
		{
			if (!(*mini_vars))
				lstadd_back(addnode(*buffer, WORD), mini_vars);
			lstadd_sub_back(add_subnode(*buffer, DOUBLE), mini_vars);
			free(*buffer);
			*buffer = NULL;
		}
		*state = NORMAL;
	}
	else if (cara >= ' ' && cara <= '~')
	{
		*buffer = add_char(*buffer, cara);
	}
}

void	in_s_quote_state(char **buffer, char cara, t_state *state, t_token **mini_vars)
{
	/* if (*buffer)
	{
		lstadd_back(addnode(*buffer, WORD), mini_vars);
		lstadd_sub_back(add_subnode(*buffer, SINGLE), mini_vars);
		free(*buffer);
		*buffer = NULL;
	} */
	//*buffer = add_char(*buffer, cara);
	if (cara == '"')
	{
		if (*buffer)
		{
			if (!(*mini_vars))
				lstadd_back(addnode(*buffer, WORD), mini_vars);
			lstadd_sub_back(add_subnode(*buffer, SINGLE), mini_vars);
			free(*buffer);
			*buffer = NULL;
		}
		//*state = IN_D_QUOTE;
	}
	else if (cara == 39)
	{
		if (*buffer)
		{
			if (!(*mini_vars))
				lstadd_back(addnode(*buffer, WORD), mini_vars);
			lstadd_sub_back(add_subnode(*buffer, SINGLE), mini_vars);
			free(*buffer);
			*buffer = NULL;
		}
		*state = NORMAL;
	}
	else if (cara >= ' ' && cara <= '~')
	{
		*buffer = add_char(*buffer, cara);
	}
}

t_token	*lexing(t_token **mini_vars, char *line)
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
			normal_state(&buffer, line[i], &state, mini_vars);
		else if (state == IN_D_QUOTE)
			in_d_quote_state(&buffer, line[i], &state, mini_vars);
		else if (state == IN_S_QUOTE)
			in_s_quote_state(&buffer, line[i], &state, mini_vars);
		i++;
	}
	if (buffer && state == NORMAL)
	{
		if (buffer[0] == '<')
		{
			lstadd_back(addnode(buffer, INFILE), mini_vars);
			lstadd_sub_back(add_subnode(buffer, NONE), mini_vars);
		}
		else if (buffer[0] == '>')
		{
			lstadd_back(addnode(buffer, OUTFILE), mini_vars);
			lstadd_sub_back(add_subnode(buffer, NONE), mini_vars);
		}
		else if (buffer[0] != '|')
		{
			lstadd_back(addnode(buffer, WORD), mini_vars);
			lstadd_sub_back(add_subnode(buffer, NONE), mini_vars);
		}
		free(buffer);
	}
	return (*mini_vars);
}
