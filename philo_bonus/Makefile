FILES = main.c handle_args.c utiles.c

NAME = philo_bonus

CFLAGS = -Wall -Wextra -Werror

OBJ = ${FILES:.c=.o}

all:$(NAME)
$(NAME):$(OBJ)
	cc $(CFLAGS) $(OBJ) -o $(NAME)
clean:
	@rm -f $(OBJ)
	@echo "cleaning object files ..."
fclean: clean
	@rm -r $(NAME)
	@echo "Cleaning Executable File ..."
re: fclean all