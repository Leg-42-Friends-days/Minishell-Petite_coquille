# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/05 13:00:27 by mickzhan          #+#    #+#              #
#    Updated: 2026/03/11 16:24:09 by ibrouin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.SILENT:

NAME = minishell
CC = cc
CFLAGS = -I./includes -I./libft -g3
SRC_DIR = src/
SRC =	main.c \
		lexing/add_nodes.c \
		lexing/lexing_2.c \
		lexing/lexing.c \
		lexing/cara_types.c \
		lexing/node_utils.c \
		lexing/test.c \
		builtin/env.c \
		builtin/export.c \
		builtin/pwd.c \
		builtin/cd.c \
		builtin/echo.c \
		builtin/exit.c \
		builtin/unset.c \
		builtin/free_builtin.c \
		parsing/check_token.c \
		parsing/parsing.c \
		expender/expender.c \
		exec/execution.c \
		exec/path.c \
		exec/redirection.c
		
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
  ./minishell
		 

libft:
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

.PHONY: all clean fclean re val libft
