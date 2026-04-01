/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:26:52 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/27 14:42:22 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_type(char c, va_list test, int *count)
{
	if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(test, int), count);
	if (c == 'u')
		ft_putnbru(va_arg(test, unsigned int), count);
	if (c == 's')
		ft_putstr(va_arg(test, char *), count);
	if (c == '%')
		ft_putchar('%', count);
	if (c == 'c')
		ft_putchar(va_arg(test, int), count);
	if (c == 'X')
		ft_upperhexa(va_arg(test, unsigned int), count);
	if (c == 'x')
		ft_lowerhexa(va_arg(test, unsigned int), count);
	if (c == 'p')
		ft_pointer(va_arg(test, void *), count);
}

int	ft_printf(const char *s, ...)
{
	int		count;
	int		i;
	va_list	test;

	i = 0;
	count = 0;
	if (s == NULL)
		return (-1);
	va_start(test, s);
	while (s[i] != '\0')
	{
		if (s[i] != '%')
		{
			write(1, &s[i], 1);
			count ++;
		}
		else
		{
			i++;
			ft_type(s[i], test, &count);
		}
		i++;
	}
	va_end(test);
	return (count);
}
/* #include "ft_printf.h"

int	main(void)
{
	char	*t;
	char	d;
	int		cmpt;
	int		vrai;

	t = NULL;
	d = 'a';
	cmpt = 0;
	vrai = 0;
	printf("mon resultat\n");
	cmpt = ft_printf("haha %d trop drole %s mdr %%  %c\n", INT_MIN, t, d);
	printf("%d\n", cmpt);
	printf("la vraie fonction\n");
	vrai = printf("haha %d trop drole %s mdr %%  %c\n", INT_MIN, t, d);
	printf("%d\n", vrai);
	vrai = ft_printf(0);
	ft_printf("%d", vrai);
} */