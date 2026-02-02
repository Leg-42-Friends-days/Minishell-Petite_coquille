# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/05 13:00:27 by mickzhan          #+#    #+#              #
#    Updated: 2026/02/02 15:43:55 by ibrouin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes -I./libft 
SRC_DIR = src/
SRC =	main.c \
		lexing.c \

OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L./$(LIBFT_DIR) -lft


all: libft $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
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
