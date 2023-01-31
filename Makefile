NAME = philo

FILES = main.c utiles.c utiles_2.c

OBJ = ${FILES:.c=.o}

CFLAGS = -Wall -Wextra -Werror
all:${NAME}
${NAME}:${OBJ}
	@cc ${CFLAGS} $(OBJ) -o $(NAME)
	@echo "compiling ..."

clean :
	@rm -f $(OBJ)
	@echo "removing object files !"

fclean :
	@rm -f $(OBJ) $(NAME)
	@echo "removing object files and executable file !"

re : fclean all