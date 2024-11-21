# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/10 15:53:51 by cbajji            #+#    #+#              #
#    Updated: 2024/11/20 17:27:23 by cbajji           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=address
NAME = philo
SRC = philo.c parse.c super_thread.c routine.c helpers.c get_set1.c get_set2.c destroy.c
OBJ = $(SRC:.c=.o)
all         : $(NAME)

$(NAME)     : $(OBJ)
			$(CC) $(FLAGS) -o $(NAME) $(OBJ)

%.o			:	%.c philosophers.h
			$(CC) $(FLAGS)  -c $< -o $@

clean       :
			@rm -f $(OBJ)

fclean      : clean
			@rm -f $(NAME)

re          : fclean all

.PHONY      : clean