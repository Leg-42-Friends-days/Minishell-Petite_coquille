/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:13:10 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/16 19:12:38 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		if (g_signal == 0)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		//g_signal = 130;
	}
}
void	init_signals()
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
}

void	init_child_signals()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
// SIGQUIT = CTRL + '\'
// SIGINT = CTRL + C
// SIGTSTP = CTRL + Z

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
	//global->env = env_content(global->env, envp);
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
	g_signal = 0;
	init_signals();
	while (true)
	{
		g_signal = 0;
		line = readline("Minishell > ");
		if (line)
		{
			mini_vars = lexing(&mini_vars, line);
		}
		if (!line)
		{
			//if (mini_vars)
			//	ft_miniclear(&mini_vars);
			free(global->error_code);
			//if (global->ast)
			//	free_parser(global->ast);
			free(global);
			return (0);
		}
		if (*line)
			add_history(line);
		//printf("%d\n", g_signal);
		if (g_signal != 0)
		{
			*global->error_code = 130;
			g_signal = 0;
		}
		if (mini_vars)
		{
			//printmini(&mini_vars);
			global->ast = parser(&mini_vars);
			printmini(&mini_vars);
			//free_parser(global->ast);
			//run_through_here_doc(global->ast, global->env);
			//expand_function(ast, env);
			//print_tab(ast->cmd2);
			//execution(global);
			ft_miniclear(&mini_vars);
			free_parser(global->ast);
			//free_env(global->env);
			//free(global);
		}
		//printf("g_signal %d\n", g_signal);
		//printf("error_code %d\n", (*global->error_code));
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