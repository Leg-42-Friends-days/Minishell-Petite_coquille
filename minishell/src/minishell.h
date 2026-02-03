/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 10:29:52 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/03 14:32:58 by mickzhan         ###   ########.fr       */
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
	IN_S_QUOTE
}					t_state;

typedef enum e_token_type
{
	WORD,
	PIPE,
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND
}					t_token_type;

typedef struct s_token
{
	char			*var;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*previous;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*content;
	struct s_env	*next;
	struct s_env	*previous;
}					t_env;

// TOKEN
t_token				*lexing(t_token *mini_vars, char *line);
t_token				*lstfirst(t_token *lst);

void				printmini(t_token *mini);
void				ft_miniclear(t_token **lst);

// FONCTION DE L'ENVIRONNEMENT
t_env				*env_content(t_env *env, char **envp);

#endif