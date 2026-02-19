/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:29:35 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/19 15:09:54 by mickzhan         ###   ########.fr       */
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
	if (ast->type == AST_CMD)
		return (true);
	return (false);
}

bool	check_if_expendable(char *ast)
{
	int	i;

	i = 0;
	while (ast[i])
	{
		if (ast[i] == '$' && ast[i + 1] >= 33 && ast[i + 1] <= 126)
			return (true);
		i++;
	}
	return (false);
}

// bool	check_path2(char *ast, t_env *env)
// {
// 	int	i;

// 	i = 0;
// 	while (env != NULL)
// 	{
// 		i = 0;
// 		while (env->key[i] == ast[i])
// 		{
// 			i++;
// 			printf("key : %c\nast : %c\n", env->key[i], ast[i]);
// 			if (ast[i] == '\0')
// 				return (true);
// 		}
// 		env = env->next;
// 	}
// 	return (false);
// }

// bool	check_path(char *ast, t_env *env)
// {
// 	char	*str;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	// str = ft_calloc(1, (ft_strlen(ast) + 1));
// 	str = malloc(sizeof(char) * (ft_strlen(ast) + 1));
// 	if (!str)
// 		return (NULL);
// 	while (ast[i])
// 	{
// 		if (ast[i] == '$')
// 		{
// 			i++;
// 			while (ast[i])
// 			{
// 				str[j] = str[i];
// 				i++;
// 				j++;
// 			}
// 		}
// 		i++;
// 	}
// 		printf("ast value : %s\n", ast);
// 	printf("str value : %s\n", str);
// 	i = check_path2(ast, env);
// 	return (free(str), i);
// // }

// char	*app_expend(char *ast, t_env *env)
// {
// 	if (check_if_expendable(ast) == 0)
// 		return (ast);
// 	else if (check_path(ast, env) == 0)
// 	{
// 		ast = ft_strdup("TEST1");
// 		return (ast);
// 	}
// 	else
// 	{
// 		ast = ft_strdup("TEST2");
// 		return (ast);
// 	}
// 	return (ast);
// }

bool	check_path2(char *str, t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		i = 0;
		if (ft_strncmp(env->key, str, -1) == 0)
			return (true);
		env = env->next;
	}
	return (false);
}

int	len_dollars(char *ast)
{
	int	i;

	i = 0;
	while (ast[i])
	{
		if (ast[i] == ' ')
			return (i);
		i++;
	}
	return (i);
}

bool	check_path(char *ast, t_env *env)
{
	char	*str;
	int		i;
	int		j;

	if (env == NULL || ast == NULL)
		return (NULL);
	i = 0;
	while (ast[i])
	{
		j = 0;
		if (ast[i] == '$')
		{
			i++;
			j = len_dollars(ast + i);
			str = ft_substr(ast, i, j);
			if (!str)
				return (NULL);
			printf("str malloc: %s\n", str);
		}
		i++;
	}
	printf("ast value : %s\n", ast);
	printf("str value : %s\n", str);
	i = check_path2(str, env);
	return (free(str), i);
}

char	*app_expend(char *ast, t_env *env, bool state)
{
	if (check_if_expendable(ast) == 0)
		return (ast);
	else if (check_path(ast, env) == 0)
	{
		ast = ft_strdup("PAS TROUVE");
		// donc envoye vide
		return (ast);
	}
	else
	{
		if (state == true)
			ast = ft_strdup("TROUVER DOUBLE");
		else if (state == false)
			ast = ft_strdup("TROUVER NORMAL");
	}
	return (ast);
}

// changer a partir de a ne pas changer var mais mettre dans un tableau

t_ast	*call_expand(t_ast *ast, t_env *env)
{
	t_token		*current_token;
	t_sub_token	*current_sub;

	current_token = ast->cmd_token;
	while (current_token != NULL && current_token->type == WORD)
	{
		current_sub = current_token->sub_token;
		while (current_sub != NULL)
		{
			if (current_sub->quote == DOUBLE)
				current_sub->var = app_expend(current_sub->var, env, true);
			else if (current_sub->quote == NORMAL)
				current_sub->var = app_expend(current_sub->var, env, false);
			current_sub = current_sub->next;
		}
		current_token = current_token->next;
	}
	return (ast);
}

t_ast	*expand_ast_checker(t_ast *curseur, t_env *env)
{
	if (!curseur)
		return (NULL);
	if (check_if_word(curseur) == 1)
		call_expand(curseur, env);
	if (curseur->left)
		expand_ast_checker(curseur->left, env);
	if (curseur->right)
		expand_ast_checker(curseur->right, env);
	return (curseur);
}

t_ast	*expand_function(t_ast *ast, t_env *env)
{
	t_ast	*curseur;

	(void)env;
	curseur = ast;
	ast = expand_ast_checker(curseur, env);
	return (ast);
}
