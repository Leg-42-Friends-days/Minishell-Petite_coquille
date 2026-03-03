/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:01:11 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/03 15:55:31 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	prepare_here_doc(t_redir *node)
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

void	run_through_here_doc(t_ast *ast)
{
	t_ast	*current;

	current = ast;
	if (ast != NULL)
	{
		if (ast->type == AST_CMD || ast->type == AST_SUBSHELL)
		{
			if (ast->redirs)
			{
				while (ast->redirs)
				{
					if (ast->redirs->type == HEREDOC)
					{
						prepare_here_doc(ast->redirs);
						break ;
					}
					if (ast->redirs->next)
						ast->redirs = ast->redirs->next;
					else
						break ;
				}
			}
		}
		if (ast->left)
			run_through_here_doc(ast->left);
		if (ast->right)
			run_through_here_doc(ast->right);
	}
/* 	if (ast->left)
			print_ast(ast->left);
	if (ast->right)
		print_ast(ast->right);
	printf("\n"); */
}

void    redirection(t_ast *node)
{
	int	fd;

	if (!node->redirs)
		return;
	while (node->redirs)
	{
		if (node->redirs->type == 1)
		{
			fd = open(node->redirs->target->sub_token->var, O_RDONLY);
			if (fd < 0)
			{
				perror("minishell");
				exit (127);
			}
			node->redirs->stdin = dup(0);
			node->redirs->stdout = dup(1);
			dup2(fd, 0);
			close(fd);
		}
		if (node->redirs->type == 2)
		{
			fd = open(node->redirs->target->sub_token->var, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("minishell");
				exit (127);
			}
			node->redirs->stdin = dup(0);
			node->redirs->stdout = dup(1);
			dup2(fd, 1);
			close(fd);
		}
		if (node->redirs->type == 3)
		{
			//fd = open(node->redirs->fd[0], O_RDONLY);
			/* if (fd < 0)
			{
				perror("minishell");
				exit (127);
			} */
			fd = node->redirs->fd;
			//close(fd[1]);
			node->redirs->stdin = dup(0);
			node->redirs->stdout = dup(1);
			dup2(fd, 0);
			close(fd);
		}
		if (node->redirs->type == 4)
		{
			fd = open(node->redirs->target->sub_token->var, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror("minishell");
				exit (127);
			}
			node->redirs->stdin = dup(0);
			node->redirs->stdout = dup(1);
			dup2(fd, 1);
			close(fd);
		}
		node->redirs = node->redirs->next;
	}
}

void	restore_redirection(t_ast *node)
{
	if (!node->redirs)
		return;
	while (node->redirs)
	{
		if (node->redirs->type == 1)
		{
			dup2(0, node->redirs->stdin);
			close(node->redirs->stdin);
		}
		if (node->redirs->type == 2)
		{
			dup2(1, node->redirs->stdout);
			close(node->redirs->stdout);
		}
		if (node->redirs->type == 3)
		{
			dup2(0, node->redirs->stdin);
			close(node->redirs->stdin);
		}
		if (node->redirs->type == 4)
		{
			dup2(1, node->redirs->stdout);
			close(node->redirs->stdout);
		}
		node->redirs = node->redirs->next;
	}
}
