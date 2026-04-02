/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:31:21 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/02 20:39:18 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	hand(int signum)
{
	(void)signum;
	g_signal = 130;
	write(1, "\n", 1);
	close(0);
}

void	handle_sigquit(int sig)
{
	(void)sig;
	write(1, "\b\b  \b\b", 6);
}
