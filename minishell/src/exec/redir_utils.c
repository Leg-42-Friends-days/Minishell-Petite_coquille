/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:19:12 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/01 10:31:40 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	redir_stdin(t_redir *current, t_global *global, int *code)
{
	int		fd;
	char	*file;

	file = current->target->sub_token->var;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		global->error_code = 1;
		*code = 1;
		write(2, "minishell: ", 11);
		write(2, file, ft_strlen(file));
		write(2, ": ", 2);
		perror("");
		return ;
	}
	dup2(fd, 0);
	close(fd);
}

void	redir_stdout_trunc(t_redir *current, t_global *global, int *code)
{
	int		fd;
	char	*file;

	file = current->target->sub_token->var;
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		global->error_code = 1;
		*code = 1;
		write(2, "minishell: ", 11);
		write(2, file, ft_strlen(file));
		write(2, ": ", 2);
		perror("");
		return ;
	}
	dup2(fd, 1);
	close(fd);
}

void	redir_here_doc(t_redir *current, t_global *global, int *code)
{
	int	fd;

	fd = -1;
	fd = current->fd;
	if (fd < 0)
	{
		global->error_code = 1;
		*code = 1;
		write(2, "minishell: heredoc: ", 20);
		perror("");
		return ;
	}
	dup2(fd, 0);
	close(fd);
}

void	redir_stdout_append(t_redir *current, t_global *global, int *code)
{
	int		fd;
	char	*file;

	file = current->target->sub_token->var;
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		global->error_code = 1;
		*code = 1;
		write(2, "minishell: ", 11);
		write(2, file, ft_strlen(file));
		write(2, ": ", 2);
		perror("");
		return ;
	}
	dup2(fd, 1);
	close(fd);
}
