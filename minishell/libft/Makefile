# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/05 13:00:35 by mickzhan          #+#    #+#              #
#    Updated: 2026/04/01 23:15:57 by mickzhan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I .
AR = ar rcs
SRC = \
	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memchr.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_split.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_memcmp.c \
	ft_putstr_fd.c \
	Printf/ft_printf.c \
	Printf/ft_baselower16.c \
	Printf/ft_baseupper16.c \
	Printf/ft_pointer.c \
	Printf/ft_putchar.c \
	Printf/ft_putnbr.c \
	Printf/ft_putstr.c \
	Printf/ft_unsigned_putnbr.c \
	GNL/get_next_line.c \
	GNL/get_next_line_utils.c \
	ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstmap_bonus.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)
	@echo "$(NAME) ready !"


clean:
	@rm -rf $(OBJ) $(OBJ_BONUS)
	@echo "$(NAME): object file deleted"


fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): object file & library deleted"

re: fclean all

	
test:
	@$(CC) $(CFLAGS) main.c -L. -lft -o .test_libft
	@echo "$(NAME): Tester built"

.PHONY: all clean fclean re