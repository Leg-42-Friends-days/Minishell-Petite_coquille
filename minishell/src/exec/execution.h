/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:28:21 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/17 15:13:26 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../libft/libft.h"
# include "../lexing/lexer.h"
# include "../builtin/builtin.h"
# include "../parsing/parser.h"
# include "../minishell.h"
# include <readline/history.h>
# include <readline/readline.h>
// readline rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay add_history

# include <dirent.h>
# include <signal.h>
// man 3 kill
// man 3 signal
# include <sys/types.h>
// opendir() readdir() closedir()

# include <sys/ioctl.h>
// ioctl()

# include <termios.h>
// tcsetattr() tcgetattr()

# include <curses.h>
# include <term.h>
// getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
// tgetnum, tgetstr, tgoto, tputs

# include <sys/stat.h>
// stat() lstat() fstat()

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
// getenv()
# include <string.h>
# include <unistd.h>
// getcwd() chdir() isatty() ttyname() ttyslot()

typedef struct s_global t_global;

typedef struct s_exec
{
	int	exit_code;
}		        t_exec;

//EXECUTION
void	execution(t_global *global);
int	exec_cmd(t_ast *ast, t_env *env);
void	exec_pipe(t_ast *ast, t_env *env, int *error_code);
void	exec_and(t_ast *ast, t_env *env, int *error_code);
void	exec_or(t_ast *ast, t_env *env, int *error_code);
void	exec_subshell(t_ast *ast, t_env *env, int *error_code);
void	print_tab(char **tabl);

//PATH
char	*find_path(t_env *env);
char	*right_path(char **path, char *cmd);
char    *find_cmd(t_env *env, char *cmd);

//REDIRECTION
void    redirection(t_ast *node);
void	run_through_here_doc(t_ast *ast, t_env *env);
void	restore_redirection(t_ast *node);

#endif