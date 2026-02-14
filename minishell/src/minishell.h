/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 10:29:52 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/13 16:55:53 by mickzhan         ###   ########.fr       */
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

// MACRO SORTIE D'ERREUR

# define NORMAL_STATUS 0
# define ERROR_STATUS 1
# define ERROR_SYNTAX_STATUS 2
# define EXECUTABLE_NOT_POSSIBLE 126
# define COMMAND_NOT_FOUND 127
# define INTERRUPT_CTRL 130
# define QUIT_CTRL 131

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

// ARBRE SYNTAXIQUE

typedef enum e_ast_type
{
	AST_WORD,
	AST_PIPE,
	AST_AND,
	AST_OR,
	AST_SUBSHELL,
	AST_LEFT_PAR,
	AST_RIGHT_PAR
}					t_ast_type;

typedef struct s_redir
{
	t_token_type	type;
	t_token			*target;
	struct s_red	*next;
}					t_redir;

typedef struct s_ast
{
	t_ast_type		type;

	struct s_ast	*left;
	struct s_ast	*right;

	t_token			*cmd_token;
	t_redir			*redirs;
}					t_ast;

int					parser(t_token *token);

#endif