/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:44:12 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/01/14 14:40:18 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

char			*get_next_line(int fd);
unsigned int	ft_strlenn(const char *s);
char			*ft_strjoinn(char const *s1, char const *s2);
int				ft_check(char *str);
char			*ft_substrr(char const *s, unsigned int start, size_t len);

#endif
