/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:28:21 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/01 12:00:31 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../builtin/builtin.h"
# include "../lexing/lexer.h"
# include "../libft/libft.h"
# include "../minishell.h"
# include "../parsing/parser.h"
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

typedef struct s_global	t_global;

typedef struct s_exec
{
	int					exit_code;
}						t_exec;

// EXECUTION.c
void	execution(t_global *global);
void	execution_2(t_ast *ast, t_env *env, int *error_code, t_global *global);

// PATH.c
char	*find_path(t_env *env);
char	*right_path(char **path, char *cmd, int *error);
char	*find_cmd(t_env *env, char *cmd, int *error);
char	*init_path(t_ast **ast, t_env *env, int *error);

// PATH_UTILS.c
int		is_directory_first(char *cmd, int *error);
char	*is_directory_error(int *error, int *error_code, t_ast **ast);

// REDIRECTION.c
int		redirection(t_ast *node, t_global *global);
void	restore_redirection(t_ast *node);
void	join_limiter(t_redir *node);
void	join_sub_token_limiter(t_sub_token **c, char **result, char **first);
void	if_limiter(char *line, t_global *global, int *fd);

// HERE_DOC.c
void	run_through_here_doc(t_ast *ast, t_env *env, t_global *global);
int		prepare_here_doc(t_redir *node, t_global *global);
void	child_here_doc(int *fd, t_redir *node, t_global *global);
void	fill_here_doc(int *fd, t_redir **node, t_global *global);
void	close_previous_heredocs(t_redir *node);

// ERROR_EXEC.c
void	error_pid(void);
void	error_pipe(void);
int		free_all_in_child(t_global *global, char **table);
int		free_all_pipe_subshell(t_global *global);
void	free_subshell(t_global *global);

//ERROR_FREE.c
void	close_saved_fd(t_ast *ast);
void	free_before_execute(t_global *global, int error_code);

// REDIR_UTILS.c
void	redir_stdin(t_redir *current, t_global *global, int *code);
void	redir_stdout_trunc(t_redir *current, t_global *global, int *code);
void	redir_here_doc(t_redir *current, t_global *global, int *code);
void	redir_stdout_append(t_redir *current, t_global *global, int *code);

// EXEC_AST.c
int		exec_cmd(t_ast *ast, t_env *env, t_global *global);
void	exec_pipe(t_ast *ast, t_env *env, int *error_code, t_global *global);
void	exec_and(t_ast *ast, t_env *env, int *error_code, t_global *global);
void	exec_or(t_ast *ast, t_env *env, int *error_code, t_global *global);
void	exec_subshell(t_ast *ast, t_env *env, int *error_code, t_global *g);
int		is_directory(char *path, int *directory);
int		signal_value(int sig);

// EXEC_AST_UTILS.c
void	child_cmd(t_ast **ast, t_global *global);
void	pipe_first_child(t_ast **ast, int *fd, t_env **env, t_global *global);
void	pipe_second_child(t_ast **ast, int *fd, t_env **env, t_global *global);
int		is_directory(char *path, int *directory);
int		signal_value(int sig);

#endif