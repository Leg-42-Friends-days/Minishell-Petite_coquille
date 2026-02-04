/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:13:10 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/04 14:26:13 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signum)
{
	(void)signum;
	printf("\n%sMinishell >%s", RED, RESET);
}

// SIGQUIT = CTRL + '\'
// SIGINT = CTRL + C
// SIGTSTP = CTRL + Z
// signal(SIGQUIT, SIG_IGN);
// signal(SIGINT, handler);

// char	cwd[1024];

// if (getcwd(cwd, sizeof((cwd))) != NULL)
// 	printf("%s\n", cwd);
// else
// 	perror("getwcd");
//
// information a stocker

// Permet d'avoir le path pour le dossier actuel (pwd)
// elle permettra a chdir d'avoir l'information
// pour pouvoir faire cd
//

// env deja fait
// mais a voir si il y'a d'autre chose a faire?

// export permet d'ajouter directement dans l'env si il trouve un Variable=Attribue
// check avec getenv (si la variable existe deja remplace par le nouveau content)
// Sinon cree et le mettre dans env

// unset est l'equivalent de export sauf que au lieu d'ajoute dans l'env il retire
// prendre le donner avec getenv
// si elle existe l'enlever de l'env

// je suppose que exit c'est la fonction exit
// avec juste a prendre en compte le exit (number) qui prendra la valeur entre 0-255
// command not found si exit (alphabet)
// si il est dans un child il doit quitte le child
// si superieur a 255 il est unspecified
// sinon exit sera le status de la derniere command ou 0 si il n'y a pas eu de commande

int	main(int ac, char **av, char **envp)
{
	// t_token	*mini_vars;
	t_env	*env;
	// char	*line;
	(void)av;
	(void)ac;
	// mini_vars = NULL;
	env = NULL;
	env = env_content(env, envp);
	// env = function_export(env, "Nimporte=quoi");
	// env = function_export(env, "test==hello");
	// env = function_export(env, "Hi");
	// le cas ou il y'a un
	// export key=content
	// function_export(env);
	// while (env->next != NULL)
	// {
	// 	printf("%s", env->key);
	// 	printf("=");
	// 	printf("%s\n", env->content);
	// 	env = env->next;
	// }
	// printf("%s", env->key);
	// printf("=");
	// printf("%s", env->content);
	env = lstfirst_env(env);
	while (env->next != NULL)
	{
		free(env->key);
		free(env->content);
		env = env->next;
	}
	free(env->key);
	free(env->content);
	// while (true)
	// {
	// 	line = readline("Minishell > ");
	// 	if (line)
	// 		mini_vars = lexing(mini_vars, line);
	// 	mini_vars = lstfirst(mini_vars);
	// 	printmini(mini_vars);
	// 	ft_miniclear(&mini_vars);
	// 	free(line);
	// }
}

// Test KILL
// int	main(void)
// {
// 	int pid;

// 	pid = 362178;
// 	kill(pid, SIGQUIT);
// }