/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:44:00 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/01 22:48:46 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_endline(char **rslt, char **current, int test)
{
	char	*tmp;
	char	*rest;
	char	*line;

	if (*rslt == NULL || (*rslt)[0] == '\0')
	{
		line = ft_substrr(*current, 0, test);
		rest = ft_substrr(*current, test, (ft_strlenn(*current) - test));
		free(*rslt);
		*rslt = line;
		free(*current);
		*current = rest;
		return ;
	}
	tmp = ft_substrr(*current, 0, test);
	rest = ft_substrr(*current, test, (ft_strlenn(*current) - test));
	line = ft_strjoinn(*rslt, tmp);
	free(*rslt);
	*rslt = line;
	free(*current);
	free(tmp);
	*current = rest;
}

void	ft_checkrd(char **rslt, int rd)
{
	if (rd < 0)
	{
		free(*rslt);
		*rslt = NULL;
	}
}

void	ft_ifinline(char **str_buffer, char **rslt, char **current, int fd)
{
	char	*tmp;
	int		rd;
	int		test;

	test = 0;
	while (test == 0)
	{
		tmp = ft_strjoinn(*rslt, *current);
		free(*rslt);
		*rslt = tmp;
		free(*current);
		*current = NULL;
		rd = read(fd, *str_buffer, BUFFER_SIZE);
		if (rd <= 0)
		{
			ft_checkrd(rslt, rd);
			return ;
		}
		(*str_buffer)[rd] = '\0';
		*current = ft_substrr(*str_buffer, 0, rd);
		test = ft_check(*current);
	}
	ft_endline(rslt, current, test);
}

char	*ft_gnl(char **str_buffer, char **current, int fd)
{
	int		test;
	char	*rslt;

	rslt = ft_substrr("", 0, 0);
	test = ft_check(*current);
	if (test > 0)
	{
		ft_endline(&rslt, current, test);
		free(*str_buffer);
		return (rslt);
	}
	ft_ifinline(str_buffer, &rslt, current, fd);
	free(*str_buffer);
	if (rslt == NULL || rslt[0] == '\0')
	{
		free(rslt);
		return (NULL);
	}
	return (rslt);
}

char	*get_next_line(int fd)
{
	char		*rslt;
	char		*str_buffer;
	static char	*current;
	int			rd;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (current)
			free(current);
		return (NULL);
	}
	str_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str_buffer)
		return (NULL);
	if (!current)
	{
		rd = read(fd, str_buffer, BUFFER_SIZE);
		if (rd <= 0)
			return (free(str_buffer), NULL);
		str_buffer[rd] = '\0';
		current = ft_substrr(str_buffer, 0, rd);
	}
	rslt = ft_gnl(&str_buffer, &current, fd);
	return (rslt);
}
/* 
#include "get_next_line.h"

int	main(void)
{
	char	*rslt;
	int		fd;
	
	fd = open("testt.txt", O_RDWR);
	rslt = get_next_line(fd);
	printf("ligne 1 = %s$\n", rslt);
	free(rslt);
	rslt = get_next_line(fd);
	printf("ligne 2 = %s$\n", rslt);
	free(rslt);
	rslt = get_next_line(fd);
	printf("ligne 3 = %s$\n", rslt);
	free(rslt);
	rslt = get_next_line(fd);
	printf("ligne 4 = %s$\n", rslt);
	free(rslt);
	rslt = get_next_line(fd);
	printf("ligne 5 = %s$\n", rslt);
	free(rslt);
	rslt = get_next_line(fd);
	printf("ligne 6 = %s$\n", rslt);
	free(rslt);
	rslt = get_next_line(fd);
	printf("ligne 7 = %s$\n", rslt);
	free(rslt);
	rslt = get_next_line(fd);
	printf("ligne 8 = %s$\n", rslt);
	free(rslt);
	rslt = get_next_line(fd);
	printf("ligne 9 = %s$\n", rslt);
	free(rslt);
	rslt = get_next_line(fd);
	printf("ligne 10 = %s$\n", rslt);
	free(rslt);
	rslt = get_next_line(fd);
	printf("ligne 11 = %s$\n", rslt);
	free(rslt);
	rslt = get_next_line(fd);
	printf("ligne 12 = %s$\n", rslt);
	free(rslt);
	rslt = get_next_line(fd);
	printf("ligne 13 = %s$\n", rslt);
	free(rslt);
	rslt = get_next_line(fd);
	printf("ligne 14 = %s$\n", rslt);
	free(rslt);
} */