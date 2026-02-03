/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:13:10 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/03 15:08:07 by mickzhan         ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	int		i;

	i = 0;
	(void)av;
	(void)ac;
	env = NULL;
	env = env_content(env, envp);
	while (env->next != NULL)
	{
		printf("%s", env->key);
		printf("%s\n", env->content);
		env = env->next;
	}
}

// Test KILL
// int	main(void)
// {
// 	int pid;

// 	pid = 362178;
// 	kill(pid, SIGQUIT);
// }