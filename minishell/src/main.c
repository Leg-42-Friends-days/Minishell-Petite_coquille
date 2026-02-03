/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:13:10 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/03 11:44:22 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signum)
{
	(void) signum;
	printf("\n%sMinishell >%s", RED, RESET);
}

// SIGQUIT = CTRL + '\'
// SIGINT = CTRL + C
// SIGTSTP = CTRL + Z
// signal(SIGQUIT, SIG_IGN);

int	main(void)
{
	char	*line;
	t_token	*mini_vars;

	mini_vars = NULL;
	signal(SIGINT, handler);
	while (true)
	{
		line = readline("Minishell > ");
		if (line)
			mini_vars = lexing(mini_vars, line);
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