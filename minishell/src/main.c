/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:13:10 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/04 17:35:46 by ibrouin-         ###   ########.fr       */
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
	char	*line;
	t_token	*mini_vars;
	//t_env	*env;

	(void)av;
	(void)ac;
	(void)envp;
	mini_vars = NULL;
	//env = NULL;
	//env = env_content(env, envp);
	/*AFFICHAGE D'ENV
	while (env->next != NULL)
	{
		printf("%s", env->key);
		printf("=");
		printf("%s\n", env->content);
		env = env->next;
	}
	*/
	while (true)
	{
		line = readline("Minishell > ");
		if (line)
			mini_vars = lexing(mini_vars, line);
		if (!line)
		{
			free(line);
			if (mini_vars)
				ft_miniclear(&mini_vars);
			return (0);
		}
		// -> si NULL -> alors ctrl+D a ete actionne
		mini_vars = lstfirst(mini_vars);
		printmini(mini_vars);
		ft_miniclear(&mini_vars);
		free(line);
	}
}

// Test KILL
// int	main(void)
// {
// 	int pid;

// 	pid = 362178;
// 	kill(pid, SIGQUIT);
// }