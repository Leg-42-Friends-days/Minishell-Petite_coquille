/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:29:35 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/06 18:45:38 by mickzhan         ###   ########.fr       */
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
		if (str[i] == '$' && str[i + 1] != ':' && str[i + 1] != '=' && str[i
			+ 1] != '"' && str[i + 1] != '\'')
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

char	*check_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
		return (key = number_str(str));
	while ((str[i] != ' ' && str[i]) && (str[i] != '$' && str[i])
		&& (str[i] != 34 && str[i]) && (str[i] != 39 && str[i])
		&& (str[i] != '\'' && str[i]) && str[i] != '*')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while ((str[i] != ' ' && str[i]) && (str[i] != '$' && str[i])
		&& (str[i] != 34 && str[i]) && (str[i] != 39 && str[i])
		&& (str[i] != '\'' && str[i]) && str[i] != '*')
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
				+ 1] == '\0') && new_str[i + 1] != '"' && new_str[i + 1] != '/')
		{
			i++;
			// printf("AFFICHAGE STR %s\n", str);
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

int	expand_len(t_ast *ast)
{
	int			i;
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
				i++;
			else if (sub_token->quote == SINGLE)
				i++;
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
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
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
	if (!str || !*str)
		return (NULL);
	full_string = ft_calloc(1, 1);
	while (str[i])
	{
		full_string = strjoin_exp(full_string, str[i]);
		i++;
	}
	return (full_string);
}

char	*remove_dollar(char *str)
{
	int		len;
	int		i;
	char	*new_str;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '$')
	{
		new_str = malloc(sizeof(char) * len);
		if (!new_str)
			return (str);
		i = 0;
		while (i < len - 1)
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i] = '\0';
		return (free(str), new_str);
	}
	return (str);
}

bool	check_if_wildcard(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (false);
		i++;
	}
	return (true);
}

bool	only_wildcard(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '*')
			return (false);
		i++;
	}
	return (true);
}

bool	first_letter(char *str)
{
	int i;

	i = 0;
	if (str[i] == '.')
		return (true);
	return (false);
}
int		call_all_dir(t_ast *ast)
{
	struct dirent	*entry;
	char			*dir;
	DIR				*dp;
	int				i;
	
	i = 0;
	dir = ".";
	dp = opendir(dir);
	if (!dp)
		return (i);
	while (ast->cmd2[i])
	{
		// printf("%s\n", ast->cmd2[i]);
		i++;
	}
	entry = readdir(dp);
	while (entry)
	{
		if (first_letter(entry->d_name) == false)
		{
			ast->cmd2[i] = ft_strdup(entry->d_name);
			// printf("%s\n", ast->cmd2[i]);
			i++;
		}
		entry = readdir(dp);
	}
	return (i);
}

int	wild_card_len(void)
{
	struct dirent	*entry;
	char			*dir;
	DIR				*dp;
	int				i;

	i = 0;
	dir = ".";
	dp = opendir(dir);
	if (!dp)
		return (0);
	entry = readdir(dp);
	while (entry)
	{
		i++;
		entry = readdir(dp);
	}
	return (i);
}

int	expand_wildcard(char *str, t_ast *ast, int *index)
{
	if (check_if_wildcard(str) == true)
	{
		// printf("STR : %s\n", str);
		return (*index);
	}
	else
	{
		if (only_wildcard(str) == true)
			*index += call_all_dir(ast);
	}
	// printf("INDEX : %d\n", *index);
	return (*index);
}

t_ast	*call_expand(t_ast *ast, t_env *env)
{
	t_token		*current_token;
	t_sub_token	*current_sub;
	int			i;
	int			k;

	k = 0;
	current_token = ast->cmd_token;
	while (current_token != NULL && current_token->type == WORD)
	{
		i = 0;
		current_sub = current_token->sub_token;
		while (current_sub != NULL)
		{
			if (!(current_sub->quote == NORMAL && ft_strncmp(current_sub->var,
						"$", -1) == 0 && current_sub->next
					&& (current_sub->next->quote == DOUBLE
						|| current_sub->next->quote == SINGLE)))
			{
				if (current_sub->quote == DOUBLE)
				{
					current_sub->var = app_expend(current_sub->var, env, true);
					ast->cmd[i] = ft_strdup(current_sub->var);
					i++;
				}
				else if (current_sub->quote == NORMAL)
				{
					if (current_sub->next && (current_sub->next->quote == DOUBLE
							|| current_sub->next->quote == SINGLE))
						current_sub->var = remove_dollar(current_sub->var);
					current_sub->var = app_expend(current_sub->var, env, false);
					k = expand_wildcard(current_sub->var, ast, &k);
					ast->cmd[i] = ft_strdup(current_sub->var);
					i++;
				}
				else if (current_sub->quote == SINGLE)
				{
					ast->cmd[i] = ft_strdup(current_sub->var);
					i++;
				}
				current_sub = current_sub->next;
			}
			else
				current_sub = current_sub->next;
		}
		ast->cmd[i] = NULL;
		ast->cmd2[k] = call_join(ast->cmd);
		k++;
		current_token = current_token->next;
	}
	ast->cmd2[k] = NULL;
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

int	expand_len_token(t_ast *ast)
{
	int		i;
	t_token	*token;

	i = 0;
	token = ast->cmd_token;
	while (token != NULL && token->type == WORD)
	{
		if (check_if_wildcard(token->sub_token->var) == false)
		{
			if (only_wildcard(token->sub_token->var) == true)
				i += wild_card_len();
		}
		i++;
		token = token->next;
	}
	return (i);
}

t_ast	*expand_ast(t_ast *ast, t_env *env)
{
	t_ast	*tmp;
	int len;

	len = 0;
	tmp = ast;
	if (!ast)
		return (NULL);
	if (check_if_word(ast) == 1)
	{
		ast->cmd = malloc(sizeof(char *) * (expand_len(ast)) + 1);
		if (!ast->cmd)
			return (ast);
		ast->cmd2 = malloc(sizeof(char *) * (expand_len_token(ast) + 1));
		if (!ast->cmd2)
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
