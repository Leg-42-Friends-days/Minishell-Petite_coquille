/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:12:50 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/16 19:21:54 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../minishell.h"

bool	check_if_word(t_ast *ast);
bool	check_if_expendable(char *str);
char	*check_string(char *str, t_env *env);
char	*number_str(char *str);
bool	check_condition_key(char *str, int i);
char	*star_str(char *str);
char	*check_key(char *str);
void	copy_env(char *new_string, char *env, int *k);
void	string_advance(char *new_string, char *str, int *i, int *k);
void	check_new_string2(char *new_string, char *str, char *key, char *env);
char	*check_new_string(char *str, char *key, char *env);
void	free_new_string(char *key, char *content);
bool	check_dollar(char *str, int i);
char	*new_string2(char *new_str, int i, t_env *env);
char	*new_string(char *str, t_env *env);
char	*app_expend(char *str, t_env *env, bool state);
int		expand_len(t_ast *ast);
char	*strjoin_exp(char *s1, char *s2);
char	*call_join(char **str);
void	free_cmd(char **cmd);
char	*remove_dollar(char *str);
bool	check_if_wildcard(char *str);
bool	only_wildcard(char *str);
bool	first_letter(char *str);
int		call_all_dir(t_ast *ast, int start);
int		wild_card_len(void);
int		check_if_star_alone(char *str);
int		len_start(char *str);
int		len_start_and_star(char *str);
int		len_end(char *str);
bool	start_compare(char *str, char *entry);
bool	end_compare(char *str, char *entry);
bool	check_side(char *str, char *entry);
bool	check_inside_len(char *str, char *entry);
bool	start_wildcard(char *str);
bool	end_wildcard(char *str);
int		last_index(char **str);
bool	mid_compare(char *str, char *entry);
bool	inside_string(bool start, bool end, char **str, char *entry);
bool	check_inside_string(char *str, char *entry);
bool	check_inside(char *str, char *entry);
int		call_wild_side(t_ast *ast, char *str, int index, bool checker);
int		call_wild_multi(t_ast *ast, char *str, int index, bool checker);
int		expand_wildcard(char *str, t_ast *ast, int *index);
bool	check_if_next_token_wild(t_sub_token *sub_to);
int		len_cmd(char **str);
void	free_split(char **str);
char	*remove_null(char *str);
bool	check_dollars(t_sub_token *current_sub);
void	in_cmd(t_ast *ast, t_sub_token *current_sub, int *i);
void	normal_quote(t_ast *ast, t_sub_token *current_sub, t_env *env, int *k);
void	check_sub_status(t_ast *ast, t_sub_token *current_sub, t_env *env,
			int *pos);
void	expand_token(t_ast *ast, t_token *current_token, t_env *env,
			int *index);
t_ast	*call_expand(t_ast *ast, t_env *env);
int		expand_len_token(t_ast *ast);
void	check_redirection(t_ast *ast, t_env *env);
t_ast	*expand_ast(t_ast *ast, t_env *env);
t_ast	*expand_function(t_ast *ast, t_env *env);

#endif