/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:16:36 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/09 17:09:00 by mickzhan         ###   ########.fr       */
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
}					t_env;

typedef struct s_pwd
{
	char			*oldpwd;
	char			*pwd;
}					t_pwd;

// FONCTION DE L'ENVIRONNEMENT
t_env				*env_content(t_env *env, char **envp);
char				*get_key(char *envp);
int					find_letter(char *envp, char letter);
t_env				*function_export(t_env *env, char *test);
t_env				*lstfirst_env(t_env *lst);
t_pwd				*current_directory_path(t_pwd *pwd);
t_env				*function_unset(t_env *env, char *unset);

void				free_pwd(t_pwd *pwd);
void				free_env(t_env *env);

#endif