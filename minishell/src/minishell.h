/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 10:29:52 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/10 14:37:26 by mickzhan         ###   ########.fr       */
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
# include "lexing/lexer.h"
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
# include <stdio.h>
# include <stdlib.h>
// getenv()
# include <string.h>
# include <unistd.h>
// getcwd() chdir() isatty() ttyname() ttyslot()

typedef enum e_event
{
	UNPAIR_OP,
	OPERATOR,
	OPTION,
	BUILTIN,
	EXECUTABLE
}		t_event;

typedef enum e_exit
{
	NORMAL_STATUS,
	ERROR_STATUS,
	ERROR_SYNTAX_STATUS,
	EXECUTABLE_NOT_POSSIBLE = 126,
	COMMAND_NOT_FOUND = 127,
	INTERRUPT_CTRL = 130,
	QUIT_CTRL = 131,
}		t_exit;

typedef struct s_parser
{
	int	exit_status;
	int	event_status;

}		t_parser;

#endif