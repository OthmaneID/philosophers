FILES = main.c handle_args.c utiles.c utiles_2.c

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
	@rm -f $(NAME)
	@echo "Cleaning Executable File ..."
re: fclean all