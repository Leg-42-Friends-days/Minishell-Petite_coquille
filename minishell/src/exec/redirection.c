/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:01:11 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/04 16:58:48 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	prepare_here_doc(t_redir *node, t_env *env)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	char	*line;

	if (pipe(fd) == -1)
	{
		perror("pipe failed");
		exit (2);
	}
	pid = fork();
	//if (pid == -1)
	//	erreur;
	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			line = readline("lol > ");
			if (!line)
				break ;
			line = app_expend(line, env, 0);
			if ((ft_strncmp(line, node->target->sub_token->var, (ft_strlen(node->target->sub_token->var) + 1)) == 0))
			{
				free(line);
				close(fd[1]);
				exit (0);
			}
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	node->fd = fd[0];
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return(0);
}

void	run_through_here_doc(t_ast *ast, t_env *env)
{
	t_ast	*current;

	current = ast;
	if (ast != NULL)
	{
		if (current->type == AST_CMD || current->type == AST_SUBSHELL)
		{
			if (current->redirs)
			{
				while (current->redirs)
				{
					if (current->redirs->type == HEREDOC)
					{
						prepare_here_doc(current->redirs, env);
						break ;
					}
					if (current->redirs->next)
						current->redirs = current->redirs->next;
					else
						break ;
				}
			}
		}
		if (current->left)
			run_through_here_doc(current->left, env);
		if (current->right)
			run_through_here_doc(current->right, env);
	}
/* 	if (ast->left)
			print_ast(ast->left);
	if (ast->right)
		print_ast(ast->right);
	printf("\n"); */
}

void    redirection(t_ast *node)
{
	int		fd;
	t_redir	*current;	

	current = node->redirs;
	if (!current)
		return;
	while (current)
	{
		if (current->type == 1)
		{
			fd = open(current->target->sub_token->var, O_RDONLY);
			if (fd < 0)
			{
				perror("minishell");
				exit (127);
			}
			current->stdin = dup(0);
			current->stdout = dup(1);
			dup2(fd, 0);
			close(fd);
		}
		if (current->type == 2)
		{
			fd = open(current->target->sub_token->var, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("minishell");
				exit (127);
			}
			current->stdin = dup(0);
			current->stdout = dup(1);
			dup2(fd, 1);
			close(fd);
		}
		if (current->type == 3)
		{
			//fd = open(current->fd[0], O_RDONLY);
			/* if (fd < 0)
			{
				perror("minishell");
				exit (127);
			} */
			fd = current->fd;
			//close(fd[1]);
			current->stdin = dup(0);
			current->stdout = dup(1);
			dup2(fd, 0);
			close(fd);
		}
		if (current->type == 4)
		{
			fd = open(current->target->sub_token->var, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror("minishell");
				exit (127);
			}
			current->stdin = dup(0);
			current->stdout = dup(1);
			dup2(fd, 1);
			close(fd);
		}
		current = current->next;
	}
}

void	restore_redirection(t_ast *node)
{
	t_redir	*current;	

	current = node->redirs;
	if (!current)
		return;
	while (current)
	{
		if (current->type == 1)
		{
			dup2(current->stdin, 0);
			close(current->stdin);
		}
		if (current->type == 2)
		{
			dup2(current->stdout, 1);
			close(current->stdout);
		}
		if (current->type == 3)
		{
			dup2(current->stdin, 0);
			close(current->stdin);
		}
		if (current->type == 4)
		{
			dup2(current->stdout, 1);
			close(current->stdout);
		}
		current = current->next;
	}
}
