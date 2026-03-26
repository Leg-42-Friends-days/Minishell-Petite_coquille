/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 13:45:55 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/26 18:11:39 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	error_pid(void)
{
	perror("fork failed");
	exit (2);
}

void	error_pipe(void)
{
	perror("pipe failed");
	exit(2);
}
