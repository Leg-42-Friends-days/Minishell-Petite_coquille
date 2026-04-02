/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:29:36 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/02 20:38:18 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	if_limiter(char *line, t_global *global, int *fd)
{
	get_next_line(-1);
	free(line);
	close(fd[1]);
	free_all_in_child(global, NULL);
	exit (0);
}

void	close_previous_heredocs(t_redir *node)
{
	t_redir	*current;

	if (!node)
		return ;
	current = node;
	while (current)
	{
		if (current->type == HEREDOC && current->fd != -1)
		{
			close(current->fd);
			current->fd = -1;
		}
		current = current->next;
	}
}

int	empty_line(char *line, int *fd)
{
	if (!line)
	{
		close(fd[1]);
		return (1);
	}
	return (0);
}

void	fill_here_doc(int *fd, t_redir **node, t_global *global)
{
	char	*line;

	close_saved_fd(global->ast);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (empty_line(line, fd))
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if ((ft_strncmp(line, (*node)->target->sub_token->var,
					(ft_strlen((*node)->target->sub_token->var) + 1)) == 0))
			if_limiter(line, global, fd);
		if ((*node)->target->sub_token->quote == NONE)
			line = app_expend(line, global, 0);
		if (empty_line(line, fd))
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
}

void	child_here_doc(int *fd, t_redir *node, t_global *global)
{
	join_limiter(node);
	g_signal = 0;
	close(fd[0]);
	signal(SIGINT, hand);
	signal(SIGQUIT, handle_sigquit);
	fill_here_doc(fd, &node, global);
	get_next_line(-1);
	close(fd[1]);
	free_all_in_child(global, NULL);
	if (g_signal == 130)
		exit(130);
	exit(0);
}
