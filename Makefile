NAME = minishell

FLAGS = -Wall -Wextra -Werror 

LIBFT = ./libft/libft.a

SRC = minishell.c ft_substr2.c execution.c ./builtins/utils.c redirections.c ft_token.c \
syntax_error.c expand.c split_to_ast_node.c creat_node.c ft_free.c signal.c

OBJ = $(SRC.c=.o)

READLINE = $(shell brew --prefix readline)

all : re $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	gcc $(SRC) $(LIBFT) -lreadline -L $(READLINE)/lib -g -o $(NAME)

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