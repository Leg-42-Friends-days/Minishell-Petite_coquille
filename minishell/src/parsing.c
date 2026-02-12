/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:05:38 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/12 14:46:04 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lstfirst_token(t_token *lst)
{
	t_token	*cursor;

	if (!lst || !lst->sub_token)
		return (lst);
	cursor = lst;
	while (cursor->sub_token->prev != NULL)
		cursor->sub_token = cursor->sub_token->prev;
	return (cursor);
}

int	len_cmd(t_token *token)
{
	int		i;
	t_token	*tmp;

	i = 1;
	tmp = token;
	if (!tmp)
		return (0);
	while (tmp->next != NULL)
	{
		if (tmp->type != 0)
			i++;
		tmp = tmp->next;
	}
	if (tmp->type != 0)
		i++;
	return (i);
}

// Si "$var" geten -> "token"
// Si $var -> cree une fonction qui prend chaque separer d'un espace
// Si '$var' juste afficher $var

bool	lst_last_token(t_token *token)
{
	while (token->next != NULL)
		token = token->next;
	if (token->type != 0)
		return (true);
	return (false);
}

bool	last_next_token(t_token *token)
{
	int	i;

	i = 0;
	while (token->next != NULL)
	{
		if (token->type != 0 && token->next->type != 0)
			return (true);
		token = token->next;
	}
	return (false);
}

bool	check_token(t_token *token)
{
	if (token->type != 0 || lst_last_token(token) == 1
		|| last_next_token(token) == 1)
		return (true);
	return (false);
}

int	len_cmd_sub(t_token *token)
{
	int			i;
	t_sub_token	*tmp;

	if (!token || !token->sub_token)
		return (0);
	i = 1;
	tmp = token->sub_token;
	while (tmp->next != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**tableau_av(t_token *token)
{
	int		i;
	int		len;
	char	**tableau;
	t_sub_token *tmp;

	i = 0;
	len = len_cmd_sub(token);
	tableau = malloc(sizeof(char *) * (len + 1));
	if (!tableau)
		return (NULL);
	tmp = token->sub_token;
	while (tmp != NULL)
	{
		tableau[i] = ft_strdup(tmp->var);
		i++;
		tmp = tmp->next;
	}
	tableau[i] = NULL;
	return (tableau);
}

t_cmd	*lstadd_back_cmd(t_cmd *lst, t_token *token)
{
	t_cmd	*last;
	t_cmd	*curseur;

	(void)token;
	last = malloc(sizeof(t_cmd));
	if (!last)
		return (NULL);
	last->argv = tableau_av(token);
	last->next = NULL;
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
	return (lst);
}

t_cmd	*cmd_list(t_cmd *cmd, t_token *token)
{
	while (token != NULL)
	{
		cmd = lstadd_back_cmd(cmd, token);
		token = token->next;
	}
	return (cmd);
}

void	test_cmd(t_cmd *cmd)
{
	int i;
	
	while (cmd != NULL)
	{
		i = 0;
		while (cmd->argv[i])
		{
			printf("CMD TEST [%s]\nVALUE : [%d]\n", cmd->argv[i], i);
			i++;
		}
		cmd = cmd->next;
	}	
}

int	parser(t_token *token, t_env *env)
{
	t_cmd	*cmd;
	int		cmd_sub;

	(void)env;
	cmd = NULL;
	cmd_sub = len_cmd_sub(token);
	printf("CMD SUB LEN -> %d\n", cmd_sub);
	token = lstfirst_token(token);
	// printf("%s TEST :[%s]\n%s", RED, token->sub_token->var, RESET);
	// printf("%s TEST :[%s]\n%s", RED, token->sub_token->prev->var, RESET);
	if (check_token(token) == 1)
	{
		ft_printf(2, "PRINTF TESTER : syntax error near unexpected token\n");
		return (ERROR_SYNTAX_STATUS);
	}
	cmd = cmd_list(cmd, token);
	test_cmd(cmd);
	return (0);
}
