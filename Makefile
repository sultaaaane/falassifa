NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread -g3
SRC =	main.c \
		utils.c \
		monitor.c \
		l3acha2.c \
		routine.c \

		
OBJ = $(SRC:.c=.o)

all: $(NAME) 

$(NAME):$(OBJ)
	@make -s -C libft
	$(CC) $(SRC) $(CFLAGS) ./libft/libft.a -o $(NAME)


clean:
	rm -rf $(OBJ)
	@make -s clean -C libft
fclean: clean
	rm -rf $(NAME)
	@make -s fclean -C libft
re: fclean all
.SECONDARY: $(OBJ)