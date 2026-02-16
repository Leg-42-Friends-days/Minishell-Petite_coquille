/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:05:38 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/16 15:11:44 by mickzhan         ###   ########.fr       */
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

// int	len_cmd(t_token *token)
// {
// 	int		i;
// 	t_token	*tmp;

// 	i = 1;
// 	tmp = token;
// 	if (!tmp)
// 		return (0);
// 	while (tmp->next != NULL)
// 	{
// 		if (tmp->type != 0)
// 			i++;
// 		tmp = tmp->next;
// 	}
// 	if (tmp->type != 0)
// 		i++;
// 	return (i);
// }

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

// int	len_cmd_sub(t_token *token)
// {
// 	int			i;
// 	t_sub_token	*tmp;

// 	if (!token || !token->sub_token)
// 		return (0);
// 	i = 1;
// 	tmp = token->sub_token;
// 	while (tmp->next != NULL)
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	return (i);
// }

// char	**tableau_av(t_token *token)
// {
// 	int		i;
// 	int		len;
// 	char	**tableau;
// 	t_sub_token *tmp;

// 	i = 0;
// 	len = len_cmd_sub(token);
// 	tableau = malloc(sizeof(char *) * (len + 1));
// 	if (!tableau)
// 		return (NULL);
// 	tmp = token->sub_token;
// 	while (tmp != NULL)
// 	{
// 		tableau[i] = ft_strdup(tmp->var);
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	tableau[i] = NULL;
// 	return (tableau);
// }

// t_cmd	*lstadd_back_cmd(t_cmd *lst, t_token *token)
// {
// 	t_cmd	*last;
// 	t_cmd	*curseur;

// 	(void)token;
// 	last = malloc(sizeof(t_cmd));
// 	if (!last)
// 		return (NULL);
// 	last->argv = tableau_av(token);
// 	last->next = NULL;
// 	if (lst == NULL)
// 	{
// 		last->previous = NULL;
// 		return (last);
// 	}
// 	curseur = lst;
// 	while (curseur->next != NULL)
// 		curseur = curseur->next;
// 	curseur->next = last;
// 	last->previous = curseur;
// 	return (lst);
// }

// t_cmd	*cmd_list(t_cmd *cmd, t_token *token)
// {
// 	while (token != NULL)
// 	{
// 		cmd = lstadd_back_cmd(cmd, token);
// 		token = token->next;
// 	}
// 	return (cmd);
// }

// void	test_cmd(t_cmd *cmd)
// {
// 	int i;
// 	while (cmd != NULL)
// 	{
// 		i = 0;
// 		while (cmd->argv[i])
// 		{
// 			printf("CMD TEST [%s]\nVALUE : [%d]\n", cmd->argv[i], i);
// 			i++;
// 		}
// 		cmd = cmd->next;
// 	}
// }

// int	priority_redi(t_token *token)
// {
// 	if (!token)
// 		return (0);
// 	while (token != NULL)
// 	{
// 		if (token->type == INFILE)
// 			return (INFILE);
// 		else if (token->type == OUTFILE)
// 			return (OUTFILE);
// 		else if (token->type == HEREDOC)
// 			return (HEREDOC);
// 		else if (token->type == APPEND)
// 			return (APPEND);
// 		token = token->next;
// 	}
// 	return (0);
// }

// int	priority_pipe(t_token *token)
// {
// 	if (!token)
// 		return (0);
// 	while (token != NULL)
// 	{
// 		if (token->type == PIPE)
// 			return (PIPE);
// 		token = token->next;
// 	}
// 	return (0);
// }

// int	priority_or_and(t_token *token)
// {
// 	if (!token)
// 		return (0);
// 	while (token->prev != NULL)
// 	{
// 		if (token->type == OR)
// 			return (OR);
// 		else if (token->type == AND)
// 			return (AND);
// 		token = token->prev;
// 	}
// 	return (0);
// }

// t_ast	*lstadd_back_ast(t_ast *first, int type)
// {
// 	t_ast	*last;
// 	t_ast	*curseur;

// 	last = malloc(sizeof(t_ast));
// 	if (!last)
// 		return (NULL);
// 	curseur = first;
// 	while (curseur->left != NULL)
// 		curseur = curseur->left;
// 	curseur->left = last;
// 	last->type = type;
// 	last->left = NULL;
// 	return (first);
// }

// int	*priority_operator(t_token *token)
// {
// 	if (priority_or_and(token) != 0)
// 	{
// 		ast->type = priority_redi(token);
// 	}
// 	else if (priority_pipe(token) != 0)
// 		ast->type = priority_pipe(token);
// 	else if (priority_redi(token) != 0)
// 		ast->type = priority_redi(token);
// 	else
// 		ast->type = WORD;
// 	// token = token->next;
// 	return (ast);
// }

// t_ast	*starting_point(t_token *token, t_token *last)
// {
// 	t_ast	*ast;

// 	ast = NULL;
// 	while (last->prev != NULL)
// 	{
// 		if (priority_or_and(last) != 0)
// 		{
// 			if (ast)
// 				ast = lstadd_back_ast(ast, last->type);
// 			else
// 			{
// 				ast = malloc(sizeof(t_ast));
// 				ast->type = priority_or_and(last);
// 			}
// 		}
// 		last = last->prev;
// 	}
// 	if (priority_or_and(last) != 0)
// 		starting_point(token, last);
// 	return (ast);
// }

// int	parser(t_token *token)
// {
// 	t_ast	*ast;
// 	t_token	*last;

// 	if (check_token(token) == 1)
// 	{
// 		ft_printf(2, "PRINTF TESTER : syntax error near unexpected token\n");
// 		return (ERROR_SYNTAX_STATUS);
// 	}
// 	last = token;
// 	while (last->next != NULL)
// 		last = last->next;
// 	ast = starting_point(token, last);
// 	// ast = priority_operator(ast, token);
// 	if (ast)
// 	{
// 		printf("ast existe\n");
// 		printf("NUMBER AST : [%d]\n", ast->type);
// 	}
// 	else
// 		printf("ast n'existe pas");
// 	return (0);
// }

// Creation de node
t_ast	*ast_node(int type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->cmd_token = NULL;
	node->redirs = NULL;
	return (node);
}

t_ast	*parse_cmd(t_token **token)
{
	t_ast	*node;

	if (*token && (*token)->type == WORD)
	{
		node = ast_node(AST_WORD);
		node->cmd_token = *token;
	}
	while (*token && (*token)->type == WORD)
		*token = (*token)->next;
	while (*token && ((*token)->type == INFILE || (*token)->type == OUTFILE || (*token)->type == APPEND || (*token)->type == HEREDOC))
	{
		node->redirs = malloc(sizeof(t_redir));
		node->redirs->type = (*token)->type;
		*token = (*token)->next;
		node->redirs->target = (*token);
	}
	return (node);
}

t_ast	*parse_pipe(t_token **token)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_cmd(token);
	while (*token && (*token)->type == PIPE)
	{
		node = ast_node(AST_PIPE);
		*token = (*token)->next;
		node->left = left;
		node->right = parse_cmd(token);
		left = node;
	}
	return (left);
}

t_ast	*parse_and(t_token **token)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_pipe(token);
	while (*token && (*token)->type == AND)
	{
		node = ast_node(AST_AND);
		*token = (*token)->next;
		node->left = left;
		node->right = parse_pipe(token);
		left = node;
	}
	return (left);
}

t_ast	*parse_or(t_token **token)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_and(token);
	while (*token && (*token)->type == OR)
	{
		node = ast_node(AST_OR);
		*token = (*token)->next;
		node->left = left;
		node->right = parse_and(token);
		left = node;
	}
	return (left);
}

void	printright(t_ast *ast);

void	printleft(t_ast *ast)
{
	while (ast != NULL)
	{
		printf("AST LEFT VALUE : %u\n", ast->type);
		if (ast->cmd_token)
		{
			while (ast->cmd_token->next != NULL && ast->cmd_token->type == WORD)
			{
				printf("AST LEFT CONTENT : %s\n", ast->cmd_token->sub_token->var);
				if (ast->redirs)
				{
					printf("REDIR VALUE : %u\n", ast->redirs->type);
					printf("REDIR CONTENT : %s\n", ast->redirs->target->sub_token->var);
				}
				ast->cmd_token = ast->cmd_token->next;
			}
		}
		if (ast->right)
			printright(ast);
		ast = ast->left;
	}
	printf("\n");
}

void	printright(t_ast *ast)
{
	while (ast != NULL)
	{
		printf("AST RIGHT VALUE : %u\n", ast->type);
		if (ast->cmd_token)
			printf("AST RIGHT CONTENT : %s\n", ast->cmd_token->sub_token->var);
		// while (ast->cmd_token->sub_token->next != NULL)
		// {
		// 	printf("AST RIGHT TOKEN VALUE : %s \n", ast->cmd_token->sub_token->var);
		// 	ast->cmd_token->sub_token = ast->cmd_token->sub_token->next;
		// }
		ast = ast->right;
	}
}

int	parser(t_token *token)
{
	t_ast	*ast;

	ast = NULL;
	if (check_token(token) == 1)
	{
		ft_printf(2, "PRINTF TESTER : syntax error near unexpected token\n");
		return (ERROR_SYNTAX_STATUS);
	}
	ast = parse_or(&token);
	printleft(ast);
	printright(ast);
	return (0);
}
