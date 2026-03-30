# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/05 13:00:27 by mickzhan          #+#    #+#              #
#    Updated: 2026/03/30 13:05:36 by mickzhan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.SILENT:

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -I./includes -I./libft -g3
SRC_DIR = src/
SRC =	main.c \
		lexing/add_nodes.c \
		lexing/lexing_2.c \
		lexing/lexing.c \
		lexing/cara_types.c \
		lexing/cara_types_utils.c \
		lexing/node_utils.c \
		lexing/test.c \
		builtin/env.c \
		builtin/env2.c \
		builtin/export.c \
		builtin/export2.c \
		builtin/pwd.c \
		builtin/cd.c \
		builtin/echo.c \
		builtin/exit.c \
		builtin/unset.c \
		builtin/free_builtin.c \
		builtin/table_env.c \
		parsing/check_token.c \
		parsing/parsing.c \
		parsing/ast_redirs.c \
		parsing/ast_node_utils.c \
		parsing/ast_cmd_utils.c \
		expender/expender.c \
		exec/execution.c \
		exec/path.c \
		exec/redirection.c \
		exec/error_exec.c \
		exec/redir_utils.c \
		exec/exec_ast.c \
		exec/exec_ast_utils.c
		
OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L./$(LIBFT_DIR) -lft


all: libft $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(OBJ) -lreadline $(CFLAGS) $(LIBFT_FLAGS) -o $(NAME)
	@echo "✅ $(NAME) ready !"

clean:
	@rm -rf $(OBJ) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "✅ Removed object files"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "✅ Removed executable $(NAME)"

re: fclean all

val: 
	valgrind -s \
  --leak-check=full \
  --show-leak-kinds=all \
  --suppressions=./_devtools/readline.supp \
  --trace-children=yes \
  --track-fds=yes \
  ./minishell
		 

libft:
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

.PHONY: all clean fclean re val libft
