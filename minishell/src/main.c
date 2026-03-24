/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:13:10 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/24 15:40:50 by mickzhan         ###   ########.fr       */
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

int	len_table_env(t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		i++;
		env = env->next;
	}
	lstfirst_env(env);
	return (i);
}

char	*ft_envdup(t_env *env)
{
	char	*key;
	char	*content;
	char	*string;

	key = ft_strdup(env->key);
	string = strjoin_exp(key, "=");
	content = ft_strjoin(string, env->content);
	free(string);
	return (content);
}

char	**initiate_table_env(t_env *env)
{
	char	**table;
	int		i;

	i = 0;
	table = malloc(sizeof(char *) * (len_table_env(env) + 1));
	while (env != NULL)
	{
		table[i] = ft_envdup(env);
		i++;
		env = env->next;
	}
	table[i] = NULL;
	return (table);
}

void	print_env(char **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		printf("%s\n", table[i]);
		i++;
	}
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
	global->env = env_content(global->env, envp);
	global->env->table = initiate_table_env(global->env);
	// print_env(global->env->table);
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
			write(1, "exit\n", 5);
			if (global->env)
				free_env(global->env);
			// if (mini_vars)
			//	ft_miniclear(&mini_vars);
			free(global->error_code);
			// if (global->ast)
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
			// printmini(&mini_vars);
			global->ast = parser(&mini_vars, global);
			// printmini(&mini_vars);
			// free_parser(global->ast);
			run_through_here_doc(global->ast, global->env, global);
			// expand_function(global);
			// print_tab(global->ast->cmd2);
			execution(global);
			// printmini(&(global->head));
			ft_miniclear(&(global->head));
			free_parser(global->ast);
			mini_vars = NULL;
			// free(global);
		}
		// printf("g_signal %d\n", g_signal);
		// printf("error_code %d\n", (*global->error_code));
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