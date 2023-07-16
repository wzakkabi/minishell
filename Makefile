NAME = minishell

FLAGS = -Wall -Wextra -Werror

SRC = minishell.c

OBJ = $(SRC.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	gcc $(SRC) -lreadline -o $(NAME)

%.o : %.c
	gcc $(FLAGS) -c $<

fclean : clean
	rm -rf $(NAME)

clean :
	rm -rf $(OBJ)

re : fclean all