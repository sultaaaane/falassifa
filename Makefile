NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3 -pthread
SRC =	main.c \
		utils.c \

		
OBJ = $(SRC:.c=.o)

all: $(NAME) 

$(NAME):$(OBJ)
	@make -C libft
	$(CC) $(SRC) $(CFLAGS) ./libft/libft.a -o $(NAME)


clean:
	rm -rf $(OBJ)
	@make clean -C libft
fclean: clean
	rm -rf $(NAME)
	@make fclean -C libft
re: fclean all
.SECONDARY: $(OBJ)