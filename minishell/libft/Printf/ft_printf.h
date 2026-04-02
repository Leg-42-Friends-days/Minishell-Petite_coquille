/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 12:00:00 by mickzhan          #+#    #+#             */
/*   Updated: 2026/04/01 23:15:57 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int				ft_printf(int fd, const char *format, ...);
int				ft_putchar(char c, int fd);
int				ft_putnbr(int nb, int fd);
int				ft_putstr(char *str, int fd);
unsigned int	ft_unsigned_putnbr(unsigned int nb, int fd);
unsigned int	ft_baselower16(unsigned int nb, int fd);
unsigned int	ft_baseupper16(unsigned int nb, int fd);
int				ft_pointer(void *p, int fd);
unsigned int	ft_div_intlen(unsigned long nb);
void			base_write16(unsigned int nb, int fd);

#endif
