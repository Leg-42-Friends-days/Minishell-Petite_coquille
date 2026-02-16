/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:29:35 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/16 17:45:27 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// copy permet de copie la valeur de $
// paste permet de la mettre en leurs valeur et le renvoye 

typedef struct s_exp
{
	int				last_command;
	int				state;

	char			*copy;
	char			*paste;
	t_env			*env;
	bool			in_doc;
	struct s_exp	*next;
}					t_exp;
