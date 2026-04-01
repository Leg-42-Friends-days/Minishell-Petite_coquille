/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:22:04 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/01 11:55:35 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_directory(char *path, int *directory)
{
	struct stat	st;

	if (stat(path, &st) != 0)
	{
		perror("minishell");
		free(path);
		*directory = 127;
		return (127);
	}
	if (S_ISDIR(st.st_mode))
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": Is a directory\n", 17);
		free(path);
		*directory = 126;
		return (126);
	}
	*directory = 0;
	return (0);
}

int	signal_value(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		return (130);
	}
	if (sig == SIGQUIT)
	{
		ft_printf(1, "Quit (core dumped)\n");
		return (131);
	}
	return (0);
}

void	child_cmd(t_ast **ast, t_global *global)
{
	int		code;
	char	*path;
	int		error;
	char	**table;

	table = initiate_table_env(global->env);
	code = 0;
	error = 127;
	init_child_signals();
	code = redirection(*ast, global);
	close_saved_fd(global->ast);
	if (code == 1)
		free_before_execute(global, 1);
	path = init_path(ast, global->env, &error);
	if (!path)
		free_before_execute(global, error);
	code = 0;
	if (is_directory(path, &code) != 0)
		free_before_execute(global, code);
	execve(path, (*ast)->cmd2, table);
	free(path);
	free_all_in_child(global, table);
	perror("minishell");
	exit (127);
}

void	pipe_first_child(t_ast **ast, int *fd, t_env **env, t_global *global)
{
	int	error;

	error = 0;
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	execution_2((*ast)->left, *env, &global->error_code, global);
	close_saved_fd(global->ast);
	error = free_all_pipe_subshell(global);
	exit(error);
}

void	pipe_second_child(t_ast **ast, int *fd, t_env **env, t_global *global)
{
	int	error;

	error = 0;
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	execution_2((*ast)->right, *env, &global->error_code, global);
	close_saved_fd(global->ast);
	error = free_all_pipe_subshell(global);
	exit(error);
}
