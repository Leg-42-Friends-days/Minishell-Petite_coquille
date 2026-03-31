/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:13:10 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/31 18:34:57 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal;

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		if (g_signal == 0)
		{
			write(1, "\n", 1);
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
	global->what_free = (int *)malloc(sizeof(int));
	*global->what_free = 0;
	global->true_head = NULL;
	global->env = NULL;
	global->ast = NULL;
	if (!envp || !envp[0])
		global->env = mini_env(global->env);
	else
		global->env = env_content(global->env, envp);
	global->env->table = initiate_table_env(global->env);
	// print_env(global->env->table);
	// free_table(global->env->table);
	global->error_code = (int *)malloc(sizeof(int));
	*global->error_code = 0;
	global->here_doc_error = (int *)malloc(sizeof(int));
	*global->here_doc_error = 0;
	// affichage_env(global->env);
	g_signal = 0;
	init_signals();
	if (isatty(0))
	{
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
				write(1, "exit\n", 5);
				// free(global->what_free);
				if (global->env)
					free_env(global->env);
				free(global->error_code);
				// if (global->ast)
				//	free_parser(global->ast);
				/* if (*(global->what_free) == 1)
				{
					printf("lolilol\n");
					//free_parser(global->ast);
					//ft_miniclear(&(global->true_head));
				} */
				free(global->what_free);
				free(global->here_doc_error);
				free(global);
				rl_clear_history();
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
				if (mini_vars->type == INFILE || mini_vars->type == OUTFILE
					|| mini_vars->type == HEREDOC || mini_vars->type == APPEND)
				{
					*(global->what_free) = 1;
				}
				global->head = mini_vars;
				global->true_head = mini_vars;
				//printmini(&mini_vars);
				if (!parser(&mini_vars, global))
				{
					run_through_here_doc(global->ast, global->env, global);
					if (*(global->here_doc_error) == 0)
						execution(global);
					if (*(global->what_free) > 0)
						global->true_head = global->head;
					close_saved_fd(global->ast);
					ft_miniclear(&(global->true_head));
					free_parser(global->ast);
					// free(global->what_free);
					mini_vars = NULL;
				}
				mini_vars = NULL;
				// ft_miniclear(&(global->head));
				// printmini(&mini_vars);
				// free_parser(global->ast);
				// run_through_here_doc(global->ast, global->env, global);
				// expand_function(global);
				// print_tab(global->ast->cmd2);
				// execution(global);
				// printmini(&(global->head));
				// ft_miniclear(&(global->head));
				// free_parser(global->ast);
				// mini_vars = NULL;
				// free(global);
			}
			// printf("g_signal %d\n", g_signal);
			// printf("error_code %d\n", (*global->error_code));
			free(line);
		}
	}
}

// Test KILL
// int	main(void)
// {
// 	int pid;

// 	pid = 362178;
// 	kill(pid, SIGQUIT);
// }