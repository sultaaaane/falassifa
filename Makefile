NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g3  -fsanitize=thread
SRC =	main.c \
		utils.c \
		monitor.c \
		l3acha2.c \
		routine.c \
		utils1.c  \
		utils2.c  \

		
OBJ = $(SRC:.c=.o)

all: $(NAME) 

$(NAME):$(OBJ)
	$(CC) $(SRC) $(CFLAGS) -o $(NAME)


clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)
re: fclean all
.SECONDARY: $(OBJ)