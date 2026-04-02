/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:24:49 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/02 20:27:33 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	over_long_max(int i, const char *str, long long sign, long long res)
{
	if (sign == 1 && (res > LLONG_MAX / 10
			|| (res == LLONG_MAX / 10 && str[i] > '7')))
		return (1);
	if (sign == -1 && (res > LLONG_MAX / 10
			|| (res == LLONG_MAX / 10 && str[i] > '8')))
		return (1);
	return (0);
}
