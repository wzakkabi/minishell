NAME = minishell

FLAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a

SRC = minishell.c ft_substr2.c execution.c ./builtins/utils.c redirections.c ft_token.c \
syntax_error.c expand.c split_to_ast_node.c creat_node.c 

OBJ = $(SRC.c=.o)

all : re $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	gcc $(SRC) $(LIBFT) -lreadline -g -o $(NAME)

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