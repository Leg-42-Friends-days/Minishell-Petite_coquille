/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:29:35 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/17 17:17:15 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// copy permet de copie la valeur de $
// paste permet de la mettre en leurs valeur et le renvoye

// typedef struct s_exp
// {
// 	int				last_command;

// 	char			*copy;
// 	char			*paste;
// 	t_state			state;
// 	t_env			*env;
// 	bool			in_doc;
// 	struct s_exp	*next;
// }					t_exp;

bool	check_if_word(t_ast *ast)
{
	if (ast->type == AST_WORD)
		return (true);
	return (false);
}

bool	check_if_expendable(char *ast)
{
	int	i;

	i = 0;
	while (ast[i])
	{
		if (ast[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

bool	check_path2(char *ast, t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		i = 0;
		while (env->key[i] == ast[i])
		{
			if (ast[i] == '\0')
				return (false);
			i++;
		}
		env == env->next;
	}
	return (true);
}

bool	check_path(char *ast, t_env *env)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = ft_calloc(1, (ft_strlen(ast) + 1));
	if (!str)
		return (NULL);
	while (ast[i])
	{
		if (ast[i] == '$')
		{
			i++;
			while (ast[i])
			{
				str[j] = str[i];
				i++;
			}
		}
		i++;
	}
	i = check_path2(str, env);
	return (free(str), i);
}

char	*app_expend(char *ast, t_env *env)
{
	if (check_if_expendable(ast) == 0)
		return (ast);
	else if (check_path(ast, env) == 0)
		return (NULL);
	else
	{
	}
}

t_ast	*call_expand(t_ast *ast, t_env *env)
{
	while (ast->cmd_token != NULL)
	{
		if (ast->cmd_token->sub_token->quote != SINGLE)
			ast->cmd_token->sub_token->var = app_expend(ast->cmd_token->sub_token->var,
					env);
		ast->cmd_token = ast->cmd_token->next;
	}
	return (ast);
}

t_ast	*expand_left(t_ast *curseurl, t_env *env)
{
	while (curseurl->type != AST_WORD)
	{
		curseurl = curseurl->left;
		if (check_if_word(curseurl) == 1)
			call_expand(curseurl, env);
		else
			expand_left(curseurl->right, env);
		if (check_if_word(curseurl) == 1)
			call_expand(curseurl, env);
	}
}

t_ast	*expand_function(t_ast *ast, t_env *env)
{
	t_ast	*curseurl;
	t_ast	*curseurr;

	curseurl = ast;
	curseurr = ast;
	expand_left(curseurl, env);
	if (curseurr->type != AST_WORD)
	{
		if (curseurr->left && check_if_word(curseurr) == true)
	}
	return (ast);
}
