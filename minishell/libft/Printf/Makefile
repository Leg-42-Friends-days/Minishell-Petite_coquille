# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/25 19:32:19 by ibrouin-          #+#    #+#              #
#    Updated: 2025/11/25 19:32:27 by ibrouin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CFLAGS = -Wall -Wextra -Werror -I ./
CC = cc

SRC_FILES = ft_lowerhexa ft_pointer ft_printf ft_putnbr ft_putnbru ft_putstr ft_upperhexa

OBJ_FILES = $(addsuffix .o, $(SRC_FILES))

#BONUS_SRC = ft_lstnew_bonus ft_lstadd_front_bonus ft_lstsize_bonus ft_lstlast_bonus ft_lstadd_back_bonus ft_lstdelone_bonus ft_lstclear_bonus ft_lstiter_bonus ft_lstmap_bonus

#BONUS_OBJ = $(addsuffix .o, $(BONUS_SRC))

ARNAME = ar rcs $(NAME)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(ARNAME) $(OBJ_FILES)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#ALL_OBJS = $(OBJ_FILES) $(BONUS_OBJ)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

#bonus: $(ALL_OBJS)
	$(ARNAME) $(ALL_OBJS)

.PHONY: all clean fclean re
