/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:29:35 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/18 15:14:00 by mickzhan         ###   ########.fr       */
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
	int		env_len;
	char	*new_string;

	env_len = 0;
	if (env)
		env_len = ft_strlen(env);
	new_string = malloc(ft_strlen(str) + env_len - ft_strlen(key) + 1
			* sizeof(char));
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

bool	check_dollar(char *str, int i)
{
	if (str[i] == '$' && !(str[i + 1] == ' ' || str[i + 1] == '\0') && str[i
		+ 1] != '"' && str[i + 1] != '/')
		return (true);
	return (false);
}

int	new_string_len(char *new_str, int i, t_env *env)
{
	char	*key;
	char	*content;
	int		len;

	len = 0;
	key = check_key(new_str + i + 1);
	if (!key)
		return (0);
	content = check_string(key, env);
	if (content)
		len = ft_strlen(content);
	else
		len = ft_strlen(key) + 1;
	free(key);
	free(content);
	return (len);
}

char	*new_string2(char *new_str, int i, t_env *env)
{
	char	*key;
	char	*content;
	char	*tmp;

	key = check_key(new_str + i + 1);
	if (!key)
		return (free(new_str), NULL);
	content = check_string(key, env);
	tmp = check_new_string(new_str, key, content);
	free_new_string(key, content);
	return (tmp);
}

char	*new_string(char *str, t_env *env)
{
	int		i;
	char	*new_str;
	int		len;

	i = 0;
	new_str = ft_strdup(str);
	if (!new_str)
		return (free(str), NULL);
	while (new_str[i])
	{
		if (check_dollar(new_str, i) == true)
		{
			len = new_string_len(new_str, i, env);
			new_str = new_string2(new_str, i, env);
			if (!new_str)
				return (free(str), NULL);
			i += len;
		}
		else
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
	if (s1)
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	}
	while (s2 && s2[j])
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
	full_string = NULL;
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
	free(cmd);
}

void	free_cmd_content(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i])
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
	if (!start || !end)
		return (free(start), free(end), false);
	if (ft_strlen(start) + ft_strlen(end) > ft_strlen(entry))
		return (free(start), free(end), false);
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
	if (!str || !*str)
		return (false);
	len = last_index(str) - 1;
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
	if (only_wildcard(str) == true)
		*index = call_all_dir(ast, *index);
	else if (check_if_star_alone(str) == 1)
		*index = call_wild_side(ast, str, *index, false);
	else if (check_if_star_alone(str) > 1)
		*index = call_wild_multi(ast, str, *index, false);
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

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*remove_null(char *str)
{
	if (!str)
		return (NULL);
	if (str[0] == '\0')
		return (free(str), NULL);
	return (str);
}

bool	check_dollars(t_sub_token *current_sub)
{
	if (current_sub->quote == NORMAL && ft_strncmp(current_sub->var, "$",
			-1) == 0 && current_sub->next && (current_sub->next->quote == DOUBLE
			|| current_sub->next->quote == SINGLE))
		return (true);
	return (false);
}

bool	check_if_empty(char **split, int i)
{
	i++;
	while (split[i])
	{
		if (split[i][0] != '\0')
			return (true);
		i++;
	}
	return (false);
}

void	add_index(t_ast *ast, int *index)
{
	if (ast->cmd2[*index])
	{
		(*index)++;
		ast->cmd2[*index] = NULL;
	}
}

void	add_str_to_cmd(t_ast *ast, int *index, char *str)
{
	char	*new_str;

	if (!str)
		return ;
	if (!ast->cmd2[*index])
	{
		ast->cmd2[*index] = ft_strdup(str);
		return ;
	}
	new_str = ft_strjoin(ast->cmd2[*index], str);
	if (!new_str)
		return ;
	free(ast->cmd2[*index]);
	ast->cmd2[*index] = new_str;
}


char	*check_if_space(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (free(str), NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			new_str[j++] = ' ';
			while (str[i] && str[i] == ' ')
				i++;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*normal_value(t_sub_token *sub, t_env *env)
{
	char	*tmp;
	char	*str;
	char	*new_str;

	tmp = ft_strdup(sub->var);
	if (!tmp)
		return (NULL);
	if (sub->next && (sub->next->quote == DOUBLE || sub->next->quote == SINGLE))
		tmp = remove_dollar(tmp);
	tmp = app_expend(tmp, env, false);
	tmp = remove_null(tmp);
	if (!tmp)
		return (NULL);
	str = ft_strtrim(tmp, " ");
	free(tmp);
	if (!str || str[0] == '\0')
		return (free(str), NULL);
	new_str = check_if_space(str);
	new_str = remove_null(new_str);
	return (new_str);
}

void	add_split_words(t_ast *ast, char **split, int *index)
{
	int		i;

	i = 0;
	while (split[i])
	{
		if (split[i][0] != '\0')
		{
			add_str_to_cmd(ast, index, split[i]);
			if (check_if_empty(split, i))
				add_index(ast, index);
		}
		i++;
	}
}

void	double_quote(t_ast *ast, t_sub_token *sub, t_env *env, int *index)
{
	char	*tmp;

	tmp = ft_strdup(sub->var);
	if (!tmp)
		return ;
	tmp = app_expend(tmp, env, true);
	tmp = remove_null(tmp);
	if (!tmp)
		return ;
	add_str_to_cmd(ast, index, tmp);
	free(tmp);
}

void	single_quote(t_ast *ast, t_sub_token *sub, int *index)
{
	add_str_to_cmd(ast, index, sub->var);
}

void	normal_quote(t_ast *ast, t_sub_token *sub, t_env *env, int *index)
{
	char	*tmp;
	char	**split;
	int		space;

	tmp = normal_value(sub, env);
	if (!tmp)
		return ;
	if (check_if_next_token_wild(sub) && !check_if_wildcard(tmp))
	{
		add_index(ast, index);
		*index = expand_wildcard(tmp, ast, index);
		ast->cmd2[*index] = NULL;
		return (free(tmp));
	}
	space = (ft_strchr(tmp, ' ') != NULL);
	if (!space)
		return (add_str_to_cmd(ast, index, tmp), free(tmp));
	if (sub->prev && (sub->prev->quote == DOUBLE || sub->prev->quote == SINGLE))
		add_index(ast, index);
	split = ft_split(tmp, ' ');
	free(tmp);
	if (!split)
		return ;
	add_split_words(ast, split, index);
	free_split(split);
}

int	count_split_word(char **split)
{
	int	j;
	int	word;

	j = 0;
	word = 0;
	while (split[j])
	{
		if (split[j][0] != '\0')
			word++;
		j++;
	}
	return (word);
}

int	add_len(t_sub_token *sub, int word)
{
	int	i;

	i = 0;
	if (word > 1)
		i += (word - 1);
	if (word > 1 && sub->prev && (sub->prev->quote == DOUBLE
			|| sub->prev->quote == SINGLE))
		i++;
	return (i);
}

void	expand_token(t_ast *ast, t_token *current_token, t_env *env, int *index)
{
	t_sub_token	*current_sub;

	ast->cmd2[*index] = NULL;
	current_sub = current_token->sub_token;
	while (current_sub != NULL)
	{
		if (!check_dollars(current_sub))
		{
			if (current_sub->quote == DOUBLE)
				double_quote(ast, current_sub, env, index);
			else if (current_sub->quote == SINGLE)
				single_quote(ast, current_sub, index);
			else if (current_sub->quote == NORMAL)
				normal_quote(ast, current_sub, env, index);
		}
		current_sub = current_sub->next;
	}
	add_index(ast, index);
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
	free(ast->cmd);
	ast->cmd = NULL;
	return (ast);
}

int	wildcard_len_add(void)
{
	int	len;

	len = wild_card_len();
	if (len > 1)
		return (len - 1);
	return (0);
}

int	add_normal_len(char **split)
{
	int	i;
	int	string;
	int	len;

	i = 0;
	string = 0;
	len = 0;
	while (split[i])
	{
		if (split[i][0] != '\0')
		{
			string++;
			if (check_if_wildcard(split[i]) == false)
				len += wildcard_len_add();
		}
		i++;
	}
	if (string > 1)
		len += (string - 1);
	return (len);
}

int	check_if_add(t_sub_token *sub, t_env *env)
{
	char	*str;
	char	**split;
	int		i;
	int		word;

	i = 0;
	if (sub->quote != NORMAL)
		return (0);
	str = ft_strdup(sub->var);
	if (!str)
		return (0);
	str = app_expend(str, env, false);
	if (!str || str[0] == '\0')
		return (free(str), 0);
	if (ft_strchr(str, ' '))
	{
		split = ft_split(str, ' ');
		if (!split)
			return (free(str), 0);
		word = count_split_word(split);
		i += add_len(sub, word);
		free_split(split);
	}
	else if (check_if_wildcard(str) == false)
		i += wildcard_len_add();
	return (free(str), i);
}

int	expand_len_token(t_ast *ast, t_env *env)
{
	int			i;
	t_token		*token;
	t_sub_token	*sub_tok;

	i = 0;
	token = ast->cmd_token;
	while (token != NULL && token->type == WORD)
	{
		i++;
		sub_tok = token->sub_token;
		while (sub_tok)
		{
			i += check_if_add(sub_tok, env);
			sub_tok = sub_tok->next;
		}
		token = token->next;
	}
	return (i);
}

void	check_redirection(t_ast *ast, t_env *env)
{
	t_ast	*tmp;
	t_redir	*re;
	t_quote	quote;
	
	tmp = ast;
	if (!tmp || !tmp->redirs)
		return ;
	re = tmp->redirs;
	while (re != NULL)
	{
		if (re->target && re->target->sub_token && re->target->sub_token->var)
		{
			quote = re->target->sub_token->quote;
			if (check_if_expendable(re->target->sub_token->var) == 1
				&& quote == DOUBLE)
				re->target->sub_token->var = app_expend(re->target->sub_token->var,
						env, true);
			else if (check_if_expendable(re->target->sub_token->var) == 1
				&& quote == NORMAL)
				re->target->sub_token->var = app_expend(re->target->sub_token->var,
						env, false);
		}
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
		ast->cmd = malloc(sizeof(char *) * (expand_len_token(ast, env) + 1));
		if (!ast->cmd)
			return (ast);
		ast->cmd2 = malloc(sizeof(char *) * (expand_len_token(ast, env) + 1));
		if (!ast->cmd2)
			return (free(ast->cmd), ast->cmd = NULL, ast);
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
