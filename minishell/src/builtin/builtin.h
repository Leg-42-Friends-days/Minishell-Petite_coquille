/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:16:36 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/25 13:34:50 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdbool.h>

typedef struct s_env
{
	char			*key;
	char			*content;
	bool			free_export;
	struct s_env	*next;
	struct s_env	*previous;
	char			**table;
}					t_env;

typedef struct s_pwd
{
	char			*oldpwd;
	char			*pwd;
}					t_pwd;

// FONCTION DE L'ENVIRONNEMENT
char				*get_key(char *envp);
int					find_letter(char *envp, char letter);
t_env				*lstfirst_env(t_env *lst);

void				free_pwd(t_pwd *pwd);
void				free_env(t_env *env);

char				**initiate_table_env(t_env *env);
char				*ft_envdup(t_env *env);
int					len_table_env(t_env *env);

// ECHO
int					ft_echo(char **cmd, t_env *env);

// CD
int					ft_cd(char **cmd, t_env *env);
char				*ft_getenv(t_env *env, char *key);

// PWD
int					ft_pwd(char **cmd, t_env *env);

// EXIT
int					ft_exit(char **cmd, t_env *env, int *error_code);

// ENV
int					affichage_env(t_env *env);
t_env				*env_content(t_env *env, char **envp);
char	*strcat_env(char *s1, char *s2, int size);
char	*envjoin(char *s1, char *s2);
t_env	*lstadd_back_env(t_env *lst, char *key, char *value);



// EXPORT

bool				get_equal(char *str, int *error);
bool				not_exportable(char *str);
char				*get_content(char *test);
bool				key_exist(t_env *env, char *key, char *content);
t_env				*lstadd_back_exp(t_env *lst, char *key, char *value);
int					function_export(t_env *env, char **cmd, int *error);

// UNSET

void				remove_first_or_last(t_env *tmp);
void				remove_inside(t_env *tmp);
int					function_unset(t_env *env, char **unset);

#endif