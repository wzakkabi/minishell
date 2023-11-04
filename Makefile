NAME = minishell

FLAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a

SRC = minishell.c ft_substr2.c execution.c ./builtins/utils.c redirections.c ft_token.c \
syntax_error.c expand.c split_to_ast_node.c creat_node.c ft_free.c signal.c ./builtins/cd.c ./builtins/pwd.c ./builtins/exit.c ./builtins/env.c ./builtins/export.c ./builtins/unset.c ./builtins/echo.c ./execution2.c ./expand_herdoc.c

OBJ = $(SRC:.c=.o)

READLINE = $(shell brew --prefix readline)

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	gcc $(FLAGS) $(OBJ) $(LIBFT) -lreadline -L $(READLINE)/lib -o $(NAME)

$(LIBFT) :
	make -C ./libft

%.o : %.c
	gcc $(FLAGS) $< -c -o $@

fclean : clean
	rm -rf $(NAME)
	make -C ./libft fclean

clean :
	rm -rf $(OBJ)
	make -C ./libft clean

re : fclean all
