/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:19:12 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/22 15:16:06 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	redir_stdin(t_redir *current)
{
	int	fd;

	fd = open(current->target->sub_token->var, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		exit (127);
	}
	dup2(fd, 0);
	close(fd);
}

void	redir_stdout_trunc(t_redir *current)
{
	int	fd;

	fd = open(current->target->sub_token->var,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("minishell");
		exit (127);
	}
	dup2(fd, 1);
	close(fd);
}

void	redir_stdout_append(t_redir *current)
{
	int	fd;
	
	fd = open(current->target->sub_token->var,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("minishell");
		exit (127);
	}
	dup2(fd, 1);
	close(fd);
}
