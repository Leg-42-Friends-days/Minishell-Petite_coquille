/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:27:00 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/27 13:36:07 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>

int		ft_printf(const char *s, ...);
void	ft_putnbr(int n, int *count);
void	ft_putnbru(unsigned int n, int *count);
void	ft_putchar(char c, int *count);
void	ft_putstr(char *s, int *count);
void	ft_upperhexa(unsigned int n, int *count);
void	ft_lowerhexa(unsigned int n, int *count);
void	ft_pointer(void *n, int *count);

#endif 