/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:13:10 by mickzhan          #+#    #+#             */
/*   Updated: 2026/04/02 15:49:43 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	*init_global(char **envp)
{
	t_global	*global;
	(void)envp;

	global = (t_global *)malloc(sizeof(t_global));
	if (!global)
		return (NULL);
	global->true_head = NULL;
	global->env = NULL;
	global->ast = NULL;
	if (!envp || !envp[0])
		global->env = mini_env(global->env);
	else
		global->env = env_content(global->env, envp);
	global->error_code = 0;
	return (global);
}

void	command_line(t_token **mini_vars, t_global *global)
{
	if ((*mini_vars)->type == INFILE || (*mini_vars)->type == OUTFILE
		|| (*mini_vars)->type == HEREDOC || (*mini_vars)->type == APPEND)
		global->what_free = 1;
	global->head = *mini_vars;
	global->true_head = *mini_vars;
	//printmini(mini_vars);
	if (!parser(mini_vars, global))
	{
		run_through_here_doc(global->ast, global->env, global);
		if (global->here_doc_error == 0)
			execution(global);
		if (global->what_free > 0)
			global->true_head = global->head;
		close_saved_fd(global->ast);
		ft_miniclear(&(global->true_head));
		free_parser(global->ast);
		*mini_vars = NULL;
	}
	*mini_vars = NULL;
}

int	control_d(t_global *global)
{
	write(1, "exit\n", 5);
	if (global->env)
		free_env(global->env);
	free(global);
	rl_clear_history();
	return (0);
}

int	loop(t_global *global, t_token *mini_vars)
{	
	char	*line;

	while (true)
	{
		global->what_free = 0;
		global->here_doc_error = 0;
		g_signal = 0;
		line = readline("Minishell > ");
		if (line)
			mini_vars = lexing(&mini_vars, line);
		if (!line)
			return (control_d(global));
		if (*line)
			add_history(line);
		if (g_signal == 130)
		{
			global->error_code = 130;
			g_signal = 0;
		}
		if (mini_vars)
			command_line(&mini_vars, global);
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_token		*mini_vars;
	t_global	*global;

	(void)av;
	(void)ac;
	mini_vars = NULL;
	global = init_global(envp);
	if (!global)
		return (1);
	g_signal = 0;
	init_signals();
	if (isatty(0))
		return (loop(global, mini_vars));
	else
		write(2, "minishell: non-interactive mode is not supported\n", 49);
}
