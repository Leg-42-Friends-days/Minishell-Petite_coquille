# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/14 13:24:00 by ibrouin-          #+#    #+#              #
#    Updated: 2026/01/14 14:45:56 by ibrouin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror -I ./
CC = cc

PRINTF_SRC = Printf/ft_lowerhexa Printf/ft_pointer Printf/ft_printf Printf/ft_putnbr Printf/ft_putnbru Printf/ft_putstr Printf/ft_upperhexa

OBJ_PRINTF = $(addsuffix .o, $(PRINTF_SRC))

SRC_FILES = ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_itoa ft_memchr ft_memcpy ft_memmove ft_memcmp ft_memset ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd ft_split ft_strchr ft_strdup ft_striteri ft_strjoin ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp ft_strnstr ft_strrchr ft_strtrim ft_substr ft_tolower ft_toupper GNL/get_next_line GNL/get_next_line_utils

OBJ_FILES = $(addsuffix .o, $(SRC_FILES))

BONUS_SRC = ft_lstnew_bonus ft_lstadd_front_bonus ft_lstsize_bonus ft_lstlast_bonus ft_lstadd_back_bonus ft_lstdelone_bonus ft_lstclear_bonus ft_lstiter_bonus ft_lstmap_bonus

BONUS_OBJ = $(addsuffix .o, $(BONUS_SRC))

ARNAME = ar rcs $(NAME)

all: $(NAME)

$(NAME): $(OBJ_FILES) $(OBJ_PRINTF)
	$(ARNAME) $(OBJ_FILES) $(OBJ_PRINTF)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

ALL_OBJS = $(OBJ_FILES) $(OBJ_PRINTF) $(BONUS_OBJ)

clean:
	rm -f $(OBJ_FILES) $(OBJ_PRINTF) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(ALL_OBJS)
	$(ARNAME) $(ALL_OBJS)

.PHONY: all clean fclean re bonus
