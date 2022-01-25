# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 20:08:26 by dirony            #+#    #+#              #
#    Updated: 2021/12/27 20:28:03 by dirony           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

HEADER = pipex.h

HEADER_B = pipex_bonus.h 

SRC = 		main.c			ft_split.c\
			string_utils.c	parse_utils.c\
			list_utils.c	error_utils.c

SRC_BONUS = 	main_bonus.c					ft_split_bonus.c\
				string_utils_bonus.c			parse_utils_bonus.c\
				list_utils_bonus.c				error_utils_bonus.c\
				get_next_line_bonus.c			get_next_line_utils_bonus.c\
				heredoc_utils_bonus.c				

OBJ = ${SRC:.c=.o}

OBJ_BONUS = ${SRC_BONUS:.c=.o}

CFLAGS = -Wall -Werror -Wextra

COMPILE = gcc $(CFLAGS)

REMOVE = rm -f

%.o 	:	%.c	$(HEADER)
			$(COMPILE) -c $< -o $@

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@$(COMPILE) $(OBJ) -o $(NAME)

bonus:
	@make OBJ="$(OBJ_BONUS)" HEADER="$(HEADER_B)" all

clean:
	@$(REMOVE) $(OBJ) $(OBJ_BONUS)

fclean: clean
	@$(REMOVE) $(NAME)

re: fclean all
