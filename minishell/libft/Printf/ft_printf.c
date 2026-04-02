/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:28:44 by mickzhan          #+#    #+#             */
/*   Updated: 2026/01/23 10:12:04 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	affichage(char format, int fd, va_list *ap)
{
	if (format == 'c')
		return (ft_putchar(va_arg(*ap, int), fd));
	else if (format == 's')
		return (ft_putstr(va_arg(*ap, char *), fd));
	else if (format == 'p')
		return (ft_pointer(va_arg(*ap, void *), fd));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr(va_arg(*ap, int), fd));
	else if (format == 'u')
		return (ft_unsigned_putnbr(va_arg(*ap, unsigned int), fd));
	else if (format == 'x')
		return (ft_baselower16(va_arg(*ap, unsigned int), fd));
	else if (format == 'X')
		return (ft_baseupper16(va_arg(*ap, unsigned int), fd));
	else
	{
		write(fd, &format, 1);
		return (1);
	}
}

int	ft_printf(int fd, const char *format, ...)
{
	va_list	ap;
	int		i;
	int		count;

	va_start(ap, format);
	i = 0;
	count = 0;
	if (!format)
		return (-1);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += affichage(format[i], fd, &ap);
		}
		else
			count += ft_putchar(format[i], fd);
		i++;
	}
	va_end(ap);
	return (count);
}

// int	main(void)
// {
// 	ft_printf("%c %c %c", 'C', 'M', 'H');
// 	printf(0);
// }