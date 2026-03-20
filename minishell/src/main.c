/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:13:10 by mickzhan          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/03/18 20:37:20 by ibrouin-         ###   ########.fr       */
=======
/*   Updated: 2026/03/20 14:32:12 by mickzhan         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal;

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
		// g_signal = 130;
	}
}
void	init_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
}

void	init_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
// SIGQUIT = CTRL + '\'
// SIGINT = CTRL + C
// SIGTSTP = CTRL + Z

void	affichage_env(t_env *env)
{
	while (env->next != NULL)
	{
		ft_printf(1, "%s", env->key);
		ft_printf(1, "=");
		ft_printf(1, "%s\n", env->content);
		env = env->next;
	}
	ft_printf(1, "%s", env->key);
	ft_printf(1, "=");
	ft_printf(1, "%s\n", env->content);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_token		*mini_vars;
	t_global	*global;

	// t_ast	*ast;
	// t_env	*env;
	(void)av;
	(void)ac;
	(void)envp;
	mini_vars = NULL;
	global = (t_global *)malloc(sizeof(t_global));
	global->env = NULL;
	//global->env = env_content(global->env, envp);
	global->error_code = (int *)malloc(sizeof(int));
	*global->error_code = 0;
	// affichage_env(global->env);
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
		// printf("%d\n", g_signal);
		if (g_signal != 0)
		{
			*global->error_code = 130;
			g_signal = 0;
		}
		if (mini_vars)
		{
			global->head = mini_vars;
			//printmini(&mini_vars);
			global->ast = parser(&mini_vars, global);
			//printmini(&mini_vars);
			//free_parser(global->ast);
			//run_through_here_doc(global->ast, global->env);
			//expand_function(ast, env);
			//print_tab(ast->cmd2);
			//execution(global);
			//printmini(&(global->head));
			ft_miniclear(&(global->head));
			free_parser(global->ast);
			mini_vars = NULL;
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