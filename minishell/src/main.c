/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:13:10 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/02 15:43:32 by ibrouin-         ###   ########.fr       */
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

int	main(void)
{
	char	*line;
	t_mini	*mini_vars;

	signal(SIGINT, handler);
	// signal(SIGQUIT, SIG_IGN);
	while (true)
	{

		line = readline("Minishell > ");
		if (line)
			lexing(&mini_vars, line);
		while (mini_vars->next != NULL)
		{
			printf("%s\n", mini_vars->var);
			mini_vars = mini_vars->next;
		}
		// if (*line)
		// {
			// add_history()
		// }
		printf("%s", line);
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