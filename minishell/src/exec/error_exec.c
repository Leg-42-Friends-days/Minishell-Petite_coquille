/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 13:45:55 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/21 13:46:52 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	error_pid(char **paths)
{
	free(*paths);
	perror("fork failed");
	exit (2);
}

void	error_pid_pipe(void)
{
	perror("fork failed");
	exit (2);
}

void	error_pipe(void)
{
	perror("pipe failed");
	exit(2);
}