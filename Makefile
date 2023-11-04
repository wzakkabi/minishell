NAME = minishell

FLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./sources/libft

LIBFT = ./sources/libft/libft.a

SRC = ./sources/parsing/minishell.c \
	./sources/parsing/ft_substr2.c \
	./sources/parsing/ft_token.c \
	./sources/parsing/syntax_error.c \
	./sources/parsing/expand.c \
	./sources/parsing/split_to_ast_node.c \
	./sources/parsing/creat_node.c \
	./sources/parsing/ft_free.c \
	./sources/parsing/signal.c \
	./sources/parsing//expand_herdoc.c \
	./sources/execution/execution.c \
	./sources/execution/execution2.c \
	./sources/execution/redirections.c \
	./sources/builtins/utils.c \
	./sources/builtins/cd.c \
	./sources/builtins/pwd.c \
	./sources/builtins/exit.c \
	./sources/builtins/env.c \
	./sources/builtins/export.c \
	./sources/builtins/unset.c \
	./sources/builtins/echo.c

OBJ = $(SRC:.c=.o)

READLINE = $(shell brew --prefix readline)

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	gcc $(FLAGS) $(OBJ) $(LIBFT) -lreadline -L $(READLINE)/lib -o $(NAME)

$(LIBFT) :
	make -C $(LIBFT_DIR)

%.o : %.c
	gcc $(FLAGS) $< -c -o $@

fclean : clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean

clean :
	rm -rf $(OBJ)
	make -C $(LIBFT_DIR) clean

re : fclean all

.PHONY: all clean fclean re
