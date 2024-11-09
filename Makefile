CC = cc
FLAGS = -Wall -Wextra -Werror -pthread
NAME = philo
SRC = philo.c parse.c super_thread.c routine.c helpers.c get_set1.c get_set2.c
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