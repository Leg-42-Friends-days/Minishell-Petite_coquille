/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:29:35 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/16 17:03:56 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_split(char **str);

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
	if (str[i] >= 48 && str[i] <= 57)
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	if (str[i] >= 48 && str[i] <= 57)
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

bool	check_condition_key(char *str, int i)
{
	if ((str[i] != ' ' && str[i]) && (str[i] != '$' && str[i]) && (str[i] != 34
			&& str[i]) && (str[i] != 39 && str[i]) && (str[i] != '/' && str[i])
		&& (str[i] != '*' && str[i]) && (str[i] && str[i] != ']') && (str[i]
			&& str[i] != '[') && (str[i] && str[i] != '%') && (str[i]
			&& str[i] != '{') && (str[i] && str[i] != '}') && (str[i]
			&& str[i] != '!'))
		return (true);
	return (false);
}

char	*star_str(char *str)
{
	int		i;
	char	*key;

	i = 0;
	if (str[i] == '*')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	if (str[i] == '*')
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
	if (str[i] == '*')
		return (key = star_str(str));
	while (check_condition_key(str, i) == true)
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (check_condition_key(str, i) == true)
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

void	copy_env(char *new_string, char *env, int *k)
{
	int	j;

	j = 0;
	while (env && env[j])
	{
		new_string[*k] = env[j];
		(*k)++;
		j++;
	}
}

void	string_advance(char *new_string, char *str, int *i, int *k)
{
	new_string[*k] = str[*i];
	(*i)++;
	(*k)++;
}

void	check_new_string2(char *new_string, char *str, char *key, char *env)
{
	int	i;
	int	k;
	int	count;

	i = 0;
	k = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$' && count == 0)
		{
			i += ft_strlen(key) + 1;
			count++;
			copy_env(new_string, env, &k);
			continue ;
		}
		string_advance(new_string, str, &i, &k);
	}
	new_string[k] = '\0';
}

char	*check_new_string(char *str, char *key, char *env)
{
	size_t	env_len;
	char	*new_string;

	env_len = 0;
	if (env)
		env_len = ft_strlen(env);
	new_string = ft_calloc(ft_strlen(str) + env_len - ft_strlen(key) + 1,
			sizeof(char));
	if (!new_string)
		return (free(str), NULL);
	check_new_string2(new_string, str, key, env);
	return (free(str), new_string);
}

void	free_new_string(char *key, char *content)
{
	if (key)
		free(key);
	if (content)
		free(content);
}

char	*new_string(char *str, t_env *env)
{
	int		i;
	char	*key;
	char	*content;
	char	*new_str;
	char	*tmp;

	i = 0;
	new_str = ft_strdup(str);
	while (new_str[i])
	{
		if (new_str[i] == '$' && !(new_str[i + 1] == ' ' || new_str[i
				+ 1] == '\0') && new_str[i + 1] != '"' && new_str[i + 1] != '/')
		{
			key = check_key(new_str + i + 1);
			content = check_string(key, env);
			tmp = check_new_string(new_str, key, content);
			new_str = tmp;
			free_new_string(key, content);
			i = -1;
		}
		i++;
	}
	return (free(str), new_str);
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

char	*strjoin_exp(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (free(s1), NULL);
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
		if (!full_string)
			return (NULL);
		i++;
	}
	return (full_string);
}

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		free(cmd[i]);
		cmd[i] = NULL;
		i++;
	}
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
		new_str = malloc(sizeof(char) * len + 1);
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
	int	i;

	i = 0;
	if (str[i] == '.')
		return (true);
	return (false);
}

int	call_all_dir(t_ast *ast, int start)
{
	struct dirent	*entry;
	DIR				*dp;
	int				i;

	i = start;
	dp = opendir(".");
	if (!dp)
		return (i);
	entry = readdir(dp);
	while (entry)
	{
		if (first_letter(entry->d_name) == false)
		{
			ast->cmd2[i] = ft_strdup(entry->d_name);
			i++;
		}
		entry = readdir(dp);
	}
	return (closedir(dp), i);
}

int	wild_card_len(void)
{
	struct dirent	*entry;
	DIR				*dp;
	int				i;

	i = 0;
	dp = opendir(".");
	if (!dp)
		return (0);
	entry = readdir(dp);
	while (entry)
	{
		i++;
		entry = readdir(dp);
	}
	return (closedir(dp), i);
}

int	check_if_star_alone(char *str)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] && str[i] == '*')
		{
			i++;
			j++;
		}
		if (0 < j)
			count++;
		else
			i++;
	}
	return (count);
}

int	len_start(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '*')
		i++;
	return (i);
}

int	len_start_and_star(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '*')
		i++;
	while (str[i] == '*')
		i++;
	return (i);
}

int	len_end(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '*')
		i++;
	while (str[i] == '*')
		i++;
	while (str[i])
	{
		i++;
		j++;
	}
	return (j);
}

bool	start_compare(char *str, char *entry)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '*')
	{
		if (str[i] != entry[i])
			return (true);
		i++;
	}
	// printf("START COMPARE TRUE : %s\n", entry);
	// printf("START COMPARE TRUE : %s\n", str);
	return (false);
}

bool	end_compare(char *str, char *entry)
{
	int	i;
	int	j;

	i = ft_strlen(str) - 1;
	j = ft_strlen(entry) - 1;
	if (j < i)
		return (true);
	while (i >= 0)
	{
		if (str[i] != entry[j])
			return (true);
		i--;
		j--;
	}
	return (false);
}

bool	check_side(char *str, char *entry)
{
	char	*start;
	char	*end;
	int		i;

	i = 0;
	start = ft_substr(str, 0, len_start(str));
	end = ft_substr(str, len_start_and_star(str), len_end(str));
	if (ft_strlen(start) + ft_strlen(end) > ft_strlen(entry))
		return (false);
	// printf("START : [%s]\n", start);
	// printf("ENTRY : [%s]\n", entry);
	// printf("END : [%s]\n", end);
	if (start_compare(start, entry) == false && end_compare(end,
			entry) == false)
		return (free(start), free(end), true);
	return (free(start), free(end), false);
}

bool	check_inside_len(char *str, char *entry)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	len = ft_strlen(entry);
	while (str[i])
	{
		if (str[i] != '*')
			count++;
		i++;
	}
	if (count > len)
		return (true);
	return (false);
}

bool	start_wildcard(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '*')
		return (true);
	return (false);
}

bool	end_wildcard(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[i] != '*')
		return (true);
	return (false);
}

int	last_index(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

bool	mid_compare(char *str, char *entry)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (entry[i])
	{
		j = 0;
		k = 0;
		while (entry[i + k] == str[j])
		{
			k++;
			j++;
			if (str[j] == '\0')
			{
				return (false);
			}
		}
		i++;
	}
	return (true);
}

bool	inside_string(bool start, bool end, char **str, char *entry)
{
	int	i;
	int	len;

	i = 0;
	len = last_index(str) - 1;
	if (!*str || !str)
		return (false);
	while (str[i])
	{
		if (start_compare(str[0], entry) == true && start == true)
			return (false);
		else if (end_compare(str[len], entry) == true && end == true)
			return (false);
		else if (mid_compare(str[i], entry) == true)
			return (false);
		i++;
	}
	return (true);
}

bool	check_inside_string(char *str, char *entry)
{
	bool	start;
	bool	end;
	char	**tableau;

	start = start_wildcard(str);
	end = end_wildcard(str);
	tableau = ft_split(str, '*');
	if (inside_string(start, end, tableau, entry) == true)
		return (free_split(tableau), false);
	return (free_split(tableau), true);
}

bool	check_inside(char *str, char *entry)
{
	if (check_inside_len(str, entry) == true)
		return (false);
	else if (check_inside_string(str, entry) == true)
		return (false);
	return (true);
}

int	call_wild_side(t_ast *ast, char *str, int index, bool checker)
{
	struct dirent	*entry;
	DIR				*dp;
	int				i;

	i = index;
	dp = opendir(".");
	if (!dp)
		return (i);
	entry = readdir(dp);
	while (entry)
	{
		if (first_letter(entry->d_name) == false && check_side(str,
				entry->d_name) == true)
		{
			ast->cmd2[i] = ft_strdup(entry->d_name);
			checker = true;
			i++;
		}
		entry = readdir(dp);
	}
	if (checker == false)
		ast->cmd2[i++] = ft_strdup(str);
	return (closedir(dp), i);
}

int	call_wild_multi(t_ast *ast, char *str, int index, bool checker)
{
	struct dirent	*entry;
	DIR				*dp;
	int				i;

	i = index;
	dp = opendir(".");
	if (!dp)
		return (i);
	entry = readdir(dp);
	while (entry)
	{
		if (first_letter(entry->d_name) == false && check_inside(str,
				entry->d_name) == true)
		{
			ast->cmd2[i] = ft_strdup(entry->d_name);
			checker = true;
			i++;
		}
		entry = readdir(dp);
	}
	if (checker == false)
		ast->cmd2[i++] = ft_strdup(str);
	return (closedir(dp), i);
}

int	expand_wildcard(char *str, t_ast *ast, int *index)
{
	if (check_if_wildcard(str) == true)
	{
		return (*index);
	}
	else
	{
		if (only_wildcard(str) == true)
			*index = call_all_dir(ast, *index);
		else if (check_if_star_alone(str) == 1)
			*index = call_wild_side(ast, str, *index, false);
		else if (check_if_star_alone(str) > 1)
			*index = call_wild_multi(ast, str, *index, false);
	}
	return (*index);
}

bool	check_if_next_token_wild(t_sub_token *sub_to)
{
	if (sub_to->next && (sub_to->next->quote == DOUBLE
			|| sub_to->next->quote == SINGLE))
		return (false);
	else if (sub_to->prev && (sub_to->prev->quote == DOUBLE
			|| sub_to->prev->quote == SINGLE))
		return (false);
	return (true);
}

int	len_cmd(char **str)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	if (!str || !*str)
		return (count);
	while (str[i])
	{
		if (str[i][j] != '\0')
			count++;
		i++;
	}
	return (count);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**remove_null(char **str)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	**cmd;

	i = 0;
	j = 0;
	k = 0;
	len = len_cmd(str);
	cmd = malloc(sizeof(char *) * (len + 1));
	while (str[i])
	{
		if (str[i][j] != '\0')
		{
			cmd[k] = ft_strdup(str[i]);
			k++;
		}
		i++;
	}
	cmd[k] = NULL;
	free_split(str);
	return (cmd);
}

bool	check_dollars(t_sub_token *current_sub)
{
	if (current_sub->quote == NORMAL && ft_strncmp(current_sub->var, "$",
			-1) == 0 && current_sub->next && (current_sub->next->quote == DOUBLE
			|| current_sub->next->quote == SINGLE))
		return (true);
	return (false);
}

void	in_cmd(t_ast *ast, t_sub_token *current_sub, int *i)
{
	ast->cmd[*i] = ft_strdup(current_sub->var);
	(*i)++;
}

void	normal_quote(t_ast *ast, t_sub_token *current_sub, t_env *env, int *k)
{
	if (current_sub->next && (current_sub->next->quote == DOUBLE
			|| current_sub->next->quote == SINGLE))
		current_sub->var = remove_dollar(current_sub->var);
	current_sub->var = app_expend(current_sub->var, env, false);
	if (check_if_next_token_wild(current_sub) == true)
		*k = expand_wildcard(current_sub->var, ast, k);
}

void	check_sub_status(t_ast *ast, t_sub_token *current_sub, t_env *env,
		int *i, int *k)
{
	if (current_sub->quote == DOUBLE)
	{
		current_sub->var = app_expend(current_sub->var, env, true);
		in_cmd(ast, current_sub, i);
	}
	else if (current_sub->quote == NORMAL)
	{
		normal_quote(ast, current_sub, env, k);
		in_cmd(ast, current_sub, i);
	}
	else if (current_sub->quote == SINGLE)
		in_cmd(ast, current_sub, i);
}

void	expand_token(t_ast *ast, t_token *current_token, t_env *env, int *index)
{
	t_sub_token	*current_sub;
	int			i;
	int			check;

	i = 0;
	check = *index;
	current_sub = current_token->sub_token;
	while (current_sub != NULL)
	{
		if (check_dollars(current_sub) == false)
			check_sub_status(ast, current_sub, env, &i, index);
		current_sub = current_sub->next;
	}
	ast->cmd[i] = NULL;
	if (*index == check)
	{
		ast->cmd2[*index] = call_join(ast->cmd);
		(*index)++;
	}
	free_cmd(ast->cmd);
}

t_ast	*call_expand(t_ast *ast, t_env *env)
{
	t_token	*current_token;
	int		index;

	index = 0;
	current_token = ast->cmd_token;
	while (current_token != NULL && current_token->type == WORD)
	{
		expand_token(ast, current_token, env, &index);
		current_token = current_token->next;
	}
	ast->cmd2[index] = NULL;
	ast->cmd2 = remove_null(ast->cmd2);
	return (ast);
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
			i += wild_card_len();
		i++;
		token = token->next;
	}
	return (i);
}

void	check_redirection(t_ast *ast, t_env *env)
{
	t_ast	*tmp;
	t_redir	*re;
	int		i;

	i = 0;
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
		// printf("VALEUR DE TMP : %s\n", tmp->cmd_token->sub_token->var);
		// printf("VALEUR TREDIR : %s\n", re->target->sub_token->var);
		// i = expand_wildcard(tmp->cmd_token->sub_token->var, tmp, &i);
		// printf("Valeur de i : %d\n", i);
		re = re->next;
	}
}

t_ast	*expand_ast(t_ast *ast, t_env *env)
{
	int	len;

	len = 0;
	if (!ast)
		return (ast);
	if (check_if_word(ast) == 1)
	{
		ast->cmd = ft_calloc(sizeof(char *), (expand_len(ast)) + 1);
		if (!ast->cmd)
			return (ast);
		ast->cmd2 = ft_calloc(sizeof(char *), (expand_len_token(ast) + 1));
		if (!ast->cmd2)
			return (ast);
		call_expand(ast, env);
	}
	check_redirection(ast, env);
	return (ast);
}

t_ast	*expand_function(t_ast *ast, t_env *env)
{
	t_ast	*curseur;

	curseur = ast;
	ast = expand_ast(curseur, env);
	return (ast);
}
