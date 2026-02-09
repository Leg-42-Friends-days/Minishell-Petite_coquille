# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/05 13:00:27 by mickzhan          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2026/02/09 16:39:37 by mickzhan         ###   ########.fr        #
=======
#    Updated: 2026/02/09 17:04:41 by mickzhan         ###   ########.fr        #
>>>>>>> mika
#                                                                              #
# **************************************************************************** #


.SILENT:

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes -I./libft 
SRC_DIR = src/
SRC =	main.c \
		lexing/lexing.c \
		node_utils.c \
		parsing.c \
		builtin/env.c \
		builtin/export.c \
		builtin/pwd.c \
		builtin/cd.c \
		builtin/echo.c \
		builtin/unset.c \
		builtin/free_builtin.c
		
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
	valgrind --trace-children=yes --leak-check=full --track-origins=yes --track-fds=yes --show-leak-kinds=all ./$(NAME) $(ARGS) || true

libft:
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

.PHONY: all clean fclean re val libft
