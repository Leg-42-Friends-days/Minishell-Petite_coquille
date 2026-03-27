/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 10:29:52 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/27 09:45:50 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Unicode Color
// Usage > printf("%s Hello World %s", COLOR, RESET);
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define RESET "\033[0m"

# include "../libft/libft.h"
# include "./builtin/builtin.h"
# include "exec/execution.h"
# include "expender/expander.h"
# include "lexing/lexer.h"
# include "parsing/parser.h"
# include <readline/history.h>
# include <readline/readline.h>
// readline rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay add_history

# include <dirent.h>
# include <signal.h>
# include <sys/wait.h>
# include <time.h>
// man 3 kill
// man 3 signal
# include <sys/types.h>
// opendir() readdir() closedir()

# include <sys/ioctl.h>
// ioctl()

# include <errno.h>
# include <termios.h>
// tcsetattr() tcgetattr()

# include <curses.h>
# include <term.h>
// getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
// tgetnum, tgetstr, tgoto, tputs

# include <sys/stat.h>
// stat() lstat() fstat()

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
// getenv()
# include <string.h>
# include <unistd.h>
// getcwd() chdir() isatty() ttyname() ttyslot()

// EXPENSION

extern int				g_signal;

typedef struct s_ast	t_ast;

typedef struct s_global
{
    int             *error_code;
	t_token			*mini_vars;
	t_ast			*ast;
	t_env           *env;
	t_token			*head;
	t_token			*true_head;
	int				*what_free;
	int				*here_doc_error;
}				t_global;

void					init_signals(void);
void					init_child_signals(void);
void					handler(int signum);

#endif