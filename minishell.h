
#ifndef MINISHELL_H
# define MINISHELL_H


#include "./libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <termcap.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum s_token
{
	PIPE, // |
	GREAT, // >
	GREAT_GREAT, // >>
	LESS, // <
	LESS_LESS, // <<
} t_token;

typedef struct s_lexer
{
	char    	*str;
	t_token        token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_ast
{
	char **cmd;
	t_lexer lexer;
	struct s_ast *next;
	struct s_ast *prev;
} t_ast;
// hello cv | test yarbi hadchi ikhdm
# endif