/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:14:19 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/02/17 18:28:16 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libft/libft.h"
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

typedef enum e_state
{
	NORMAL,
	IN_D_QUOTE,
	IN_S_QUOTE,
	ERROR
}				t_state;

typedef enum e_token_type
{
	WORD,
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND,
	L_PAR,
	R_PAR,
	PIPE,
	OR,
	AND
}				t_token_type;

typedef enum e_quote
{
	NONE,
	SINGLE,
	DOUBLE
}				t_quote;

typedef struct s_sub_token
{
	char 				*var;
	t_quote				quote;
	struct s_sub_token	*next;
	struct s_sub_token	*prev;
}				t_sub_token;

typedef struct s_token
{
	int				token_state;
	t_sub_token		*sub_token;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

// ADD_NODES
t_token	    *addnode(t_token_type type);
t_sub_token *add_subnode(char *buffer, t_quote quote);
t_token	    *find_last(t_token **lst);
void	    lstadd_back(t_token *new, t_token **lst, t_state *state);
void	    lstadd_sub_back(t_sub_token *new, t_token **lst, t_state *state);

// LEXING
t_token				*lexing(t_token **mini_vars, char *line);

// LEXING_2
char	*add_char(char *buffer, char new);
void	in_d_quote_state(char **buf, char c, t_state *st, t_token **mini);
void	in_s_quote_state(char **buf, char c, t_state *st, t_token **mini);
void	close_token(t_token **mini_vars);
void	buffer_full(t_token **mini_vars, char **buffer, t_state *state);

// CARA_TYPES
void	angles_brackets(char **buffer, char cara, t_token **mini_vars, t_state *state);
void	quotes(char **buffer, char cara, t_token **mini_vars, t_state *state);
void	meta_cara(char **buffer, char cara, t_token **mini_vars, t_state *state);
void	other_cara(char **buffer, char cara, t_token **mini_vars, t_state *state);
void	brackets(char **buffer, char cara, t_token **mini_vars, t_state *state);

// NODE_UTILS
void				printmini(t_token **mini);
void				ft_miniclear(t_token **lst);
void				ft_minidelone(t_sub_token *lst);





void *ft_malloc(size_t size);





#endif