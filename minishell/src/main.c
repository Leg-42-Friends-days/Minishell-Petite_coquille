/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:13:10 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/02 18:17:55 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signum)
{
	(void)signum;
	printf("\n%sMinishell >%s", RED, RESET);
}

// SIGQUIT = CTRL + '\'
// SIGINT = CTRL + C
// SIGTSTP = CTRL + Z
// signal(SIGQUIT, SIG_IGN);
// signal(SIGINT, handler);

t_env	*key_env(t_env *env, char *str)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(str, ':');
	env = malloc(sizeof(t_env));
	return (env);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_mini	*mini_vars;
	t_env	*env;
	int		i;

	i = 0;
	(void)av;
	while (envp[i])
	{
		i++;
	}
	mini_vars = NULL;
	while (true)
	{
		line = readline("Minishell > ");
		if (line)
		{
			mini_vars = lexing(mini_vars, line);
			mini_vars = lstfirst(mini_vars);
		}
		free(line);
	}
	return (0);
}

// Test KILL
// int	main(void)
// {
// 	int pid;

// 	pid = 362178;
// 	kill(pid, SIGQUIT);
// }