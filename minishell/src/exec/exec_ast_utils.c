/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:22:04 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/28 13:54:09 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	close_saved_fd(t_ast *ast)
{
	t_redir	*current;

	if (!ast)
		return ;
	current = ast->redirs;
	while (current)
	{
		if (current->stdin != -1)
			close(current->stdin);
		if (current->stdout != -1)
			close(current->stdout);
		if (current->fd > 2)
			close(current->fd);
		current = current->next;
	}
	close_saved_fd(ast->left);
	close_saved_fd(ast->right);
}

void	free_before_execute(t_global *global, int error_code)
{
	if (*(global->what_free) > 0)
		global->true_head = global->head;
	ft_miniclear(&(global->true_head));
	free_parser(global->ast);
	if (global->env)
		free_env(global->env);
	free(global->error_code);
	free(global->what_free);
	free(global->here_doc_error);
	free(global);
	exit (error_code);
}

void	child_cmd(t_ast **ast, t_global *global)
{
	int		code = 0;
	char	*path;
	int		directory;

	directory = 0;
	init_child_signals();
	code = redirection(*ast, global);
	close_saved_fd(global->ast);
	if (code == 1)
		free_before_execute(global, 1);
	path = init_path(ast, global->env);
	if (!path)
		free_before_execute(global, 127);
	if (is_directory(path, &directory) != 0)
		free_before_execute(global, directory);
	execve(path, (*ast)->cmd2, global->env->table);
	free(path);
	free_all_in_child(global);
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
	execution_2((*ast)->left, *env, global->error_code, global);
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
	execution_2((*ast)->right, *env, global->error_code, global);
	close_saved_fd(global->ast);
	error = free_all_pipe_subshell(global);
	exit(error);
}
