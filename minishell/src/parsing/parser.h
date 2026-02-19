/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:23:33 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/02/19 16:18:15 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// Unicode Color
// Usage > printf("%s Hello World %s", COLOR, RESET);

# include "../libft/libft.h"
# include "../lexing/lexer.h"
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
	AST_CMD,
	AST_PIPE,
	AST_AND,
	AST_OR,
	AST_SUBSHELL,
}					t_ast_type;

typedef struct s_redir
{
	t_token_type	type;
	t_token			*target;
	struct s_redir	*next;
}					t_redir;

typedef struct s_ast
{
	t_ast_type		type;

	struct s_ast	*left;
	struct s_ast	*right;

	t_token			*cmd_token;
	t_redir			*redirs;
	char 			**cmd;
}					t_ast;


//PARSING.C
int				parser(t_token *token, t_env *env);
t_ast			*parse_or(t_token **token);

//CHECK_TOKEN.C
bool	            check_token(t_token *token);

#endif