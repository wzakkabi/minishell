NAME = minishell

FLAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a

SRC = minishell.c ft_substr2.c

OBJ = $(SRC.c=.o)

all : re $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	gcc $(SRC) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT) :
	make -C ./libft

%.o : %.c
	gcc $(FLAGS) $(LIBFT) -c $<

fclean : clean
	rm -rf $(NAME)
	rm -f $(LIBFT)

clean :
	rm -rf $(OBJ)
	rm -f ./libft/*.o

re : fclean all