/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:29:35 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/03 15:25:29 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_if_word(t_ast *ast)
{
	if (ast->type == AST_CMD)
		return (true);
	return (false);
}

bool	check_if_expendable(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != ':' && str[i + 1] != '=')
			return (true);
		i++;
	}
	return (false);
}

char	*check_string(char *str, t_env *env)
{
	char	*str_env;

	if (!str)
		return (NULL);
	str_env = NULL;
	while (env != NULL)
	{
		if (ft_strncmp(env->key, str, -1) == 0)
		{
			str_env = ft_strdup(env->content);
			// printf("ENV->CONTENT : %s\n", str_env);
			break ;
		}
		env = env->next;
	}
	return (str_env);
}

char	*number_str(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] >= 48 && str[i] <= 57)
		i++;
	key = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

// char	*unique_key(char *str)
// {
// 	int i;
// 	char	*key;

// 	i = 0;
// 	while (str[i] && (str[i + 1] != ' ' || str[i + 1] != '$'))
// 		i++;
// 	key = malloc(sizeof(char) * (i + 1));

// }

char	*check_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
		return (key = number_str(str));
	while ((str[i] != ' ' && str[i]) && (str[i] != '$' && str[i]))
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while ((str[i] != ' ' && str[i]) && (str[i] != '$' && str[i])
		&& (str[i] != 39 && str[i]))
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*check_new_string(char *str, char *key, char *env)
{
	int		i;
	int		j;
	int		k;
	int		len;
	int		count;
	char	*new_string;

	i = 0;
	k = 0;
	count = 0;
	len = ft_strlen(str) + ft_strlen(env) - ft_strlen(key) - 1;
	new_string = malloc(sizeof(char) * (len + 1));
	if (!new_string)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && count == 0 && env != NULL)
		{
			i++;
			j = 0;
			i += ft_strlen(key);
			count++;
			// new_string = new_string_cpy(new_string, env, i);
			while (env[j])
			{
				new_string[k] = env[j];
				j++;
				k++;
			}
		}
		else if (env == NULL && str[i] == '$' && count == 0)
			i += ft_strlen(key) + 1;
		new_string[k] = str[i];
		i++;
		k++;
	}
	new_string[k] = '\0';
	// printf("NEW_STRING VALUE : %s\n", new_string);
	return (free(str), new_string);
}

char	*new_string(char *str, t_env *env)
{
	int		i;
	char	*key;
	char	*content;
	char	*new_str;
	char	*tmp;

	i = 0;
	// printf("VALEUR ACTUELLE DE STR : %s\n", str);
	new_str = ft_strdup(str);
	// printf("VALEUR ACTUELLE DE NEW_STR : %s\n", new_str);
	while (new_str[i])
	{
		if (new_str[i] == '$' && !(new_str[i + 1] == ' ' || new_str[i
				+ 1] == '\0'))
		{
			i++;
			key = check_key(new_str + i);
			content = check_string(key, env);
			// printf("KEY->CONTENT : %s\n", key);
			// printf("ENV->CONTENT : %s\n", content);
			tmp = check_new_string(new_str, key, content);
			new_str = tmp;
			i = 0;
		}
		// printf("VALEUR ACTUELLE DE NEW_CHAR : %c\n", new_str[i]);
		i++;
	}
	free(str);
	return (new_str);
}

char	*app_expend(char *str, t_env *env, bool state)
{
	if (!str)
		return (NULL);
	if (check_if_expendable(str) == 0)
		return (str);
	else
	{
		if (state == true)
			str = new_string(str, env);
		else if (state == false)
			str = new_string(str, env);
	}
	return (str);
}

int	count_tmp(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	expand_len(t_ast *ast, t_env *env)
{
	int			i;
	char		**tmp;
	t_token		*token;
	t_sub_token	*sub_token;

	i = 0;
	token = ast->cmd_token;
	while (token != NULL && token->type == WORD)
	{
		sub_token = token->sub_token;
		while (sub_token != NULL)
		{
			if (sub_token->quote == DOUBLE)
				i++;
			else if (sub_token->quote == NORMAL)
			{
				sub_token->var = app_expend(sub_token->var, env, false);
				tmp = ft_split(sub_token->var, ' ');
				i += count_tmp(tmp);
			}
			sub_token = sub_token->next;
		}
		token = token->next;
	}
	return (i);
}
// dans le return (free_split(tmp));

// t_ast	*expension(t_ast *ast, t_sub_token *current_sub, t_env *env)
// {
// 	char	**tmp;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	if (current_sub->quote == DOUBLE)
// 	{
// 		current_sub->var = app_expend(current_sub->var, env, true);
// 		ast->cmd[i] = ft_strdup(current_sub->var);
// 		i++;
// 	}
// 	else if (current_sub->quote == NORMAL)
// 	{
// 		current_sub->var = app_expend(current_sub->var, env, false);
// 		tmp = ft_split(current_sub->var, ' ');
// 		while (tmp[j])
// 		{
// 			ast->cmd[i] = ft_strdup(tmp[j]);
// 			j++;
// 			i++;
// 		}
// 	}
// 	return (ast->cmd[i] = NULL, ast);
// }

// t_ast	*call_expand(t_ast *ast, t_env *env)
// {
// 	t_token		*current_token;
// 	t_sub_token	*current_sub;
// 	int			i;

// 	current_token = ast->cmd_token;
// 	while (current_token != NULL && current_token->type == WORD)
// 	{
// 		current_sub = current_token->sub_token;
// 		while (current_sub != NULL)
// 		{
// 			ast = expension(ast, current_sub, env);
// 			current_sub = current_sub->next;
// 		}
// 		current_token = current_token->next;
// 	}
// 	i = 0;
// 	while (ast->cmd[i])
// 	{
// 		printf("PRINT CMD : %s\n", ast->cmd[i]);
// 		i++;
// 	}
// 	return (ast);
// }

char	*strjoin_exp(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (len + 1));
	if (!s1 && !s2)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	if (s1)
		free(s1);
	return (str);
}

char	*call_join(char **str)
{
	int		i;
	char	*full_string;

	i = 0;
	full_string = calloc(1, 1);
	while (str[i])
	{
		full_string = strjoin_exp(full_string, str[i]);
		i++;
	}
	return (full_string);
}

t_ast	*call_expand(t_ast *ast, t_env *env)
{
	t_token		*current_token;
	t_sub_token	*current_sub;
	char		**tmp;
	int			i;
	int			k;
	int			j;

	k = 0;
	ast->cmd2 = malloc(sizeof(char *) * 10);
	current_token = ast->cmd_token;
	while (current_token != NULL && current_token->type == WORD)
	{
		i = 0;
		current_sub = current_token->sub_token;
		while (current_sub != NULL)
		{
			j = 0;
			if (current_sub->quote == DOUBLE)
			{
				current_sub->var = app_expend(current_sub->var, env, true);
				ast->cmd[i] = ft_strdup(current_sub->var);
				i++;
			}
			else if (current_sub->quote == NORMAL)
			{
				current_sub->var = app_expend(current_sub->var, env, false);
				tmp = ft_split(current_sub->var, ' ');
				while (tmp[j])
				{
					ast->cmd[i] = ft_strdup(tmp[j]);
					j++;
					i++;
				}
			}
			else if (current_sub->quote == SINGLE)
			{
				ast->cmd[i] = ft_strdup(current_sub->var);
				i++;
			}
			current_sub = current_sub->next;
		}
		ast->cmd[i] = NULL;
		ast->cmd2[k] = call_join(ast->cmd);
		k++;
		current_token = current_token->next;
	}
	// i = 0;
	// while (ast->cmd[i])
	// {
	// 	printf("%s\n", ast->cmd[i]);
	// 	i++;
	// }
	return (ast);
}

void	check_redirection(t_ast *ast, t_env *env)
{
	t_ast	*tmp;
	t_redir	*re;

	tmp = ast;
	if (!tmp || !tmp->redirs)
		return ;
	re = tmp->redirs;
	while (re != NULL)
	{
		if (check_if_expendable(re->target->sub_token->var) == 1
			&& tmp->cmd_token->sub_token->quote == DOUBLE)
			re->target->sub_token->var = app_expend(re->target->sub_token->var,
					env, true);
		else if (check_if_expendable(re->target->sub_token->var) == 1
			&& tmp->cmd_token->sub_token->quote == NORMAL)
			re->target->sub_token->var = app_expend(re->target->sub_token->var,
					env, false);
		re = re->next;
	}
}

t_ast	*expand_ast(t_ast *ast, t_env *env)
{
	t_ast	*tmp;

	tmp = ast;
	if (!ast)
		return (NULL);
	if (check_if_word(ast) == 1)
	{
		ast->cmd = malloc(sizeof(char *) * (expand_len(ast, env) + 1));
		if (!ast->cmd)
			return (ast);
		call_expand(ast, env);
	}
	check_redirection(ast, env);
	return (tmp);
}

t_ast	*expand_function(t_ast *ast, t_env *env)
{
	t_ast	*curseur;

	curseur = ast;
	ast = expand_ast(curseur, env);
	return (ast);
}
