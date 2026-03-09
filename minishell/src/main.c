/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:13:10 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/09 17:58:34 by ibrouin-         ###   ########.fr       */
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
	//t_ast	*ast;
	//t_env	*env;
	t_global	*global;

	(void)av;
	(void)ac;
	(void)envp;
	mini_vars = NULL;
	global = (t_global *)malloc(sizeof(t_global));
	global->env = NULL;
	global->env = env_content(global->env, envp);
	global->error_code = (int *)malloc(sizeof(int));
	*global->error_code = 0;
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
		{
			mini_vars = lexing(&mini_vars, line);
		}
		if (*line)
			add_history(line);
		if (!line)
		{
			free(line);
			if (mini_vars)
				ft_miniclear(&mini_vars);
			return (0);
		}
		if (mini_vars)
		{
			//printmini(&mini_vars);
			global->ast = parser(&mini_vars);
			run_through_here_doc(global->ast, global->env);
			//expand_function(ast, env);
			//print_tab(ast->cmd2);
			execution(global);
			printf("error_code %d\n", (*global->error_code));
			ft_miniclear(&mini_vars);
		}
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