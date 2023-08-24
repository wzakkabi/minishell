
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
	GREAT, // >
	GREAT_GREAT, // >>
	LESS, // <
	LESS_LESS, // <<
	PIPE,
} t_token;

typedef struct s_lexer
{
	char    	*word;
	t_token        token;
	int num_node; // hadi bach n3erfo ach mn node bach hta ila bina n7ydoha ola n expandiwha tjina eazy
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_ast
{
	char                    **str;
	int                     num_redirections;
	char                    *hd_file_name;
	t_lexer                 *redirections;
	struct s_ast			*next;
	struct s_ast			*prev;
} t_ast;
void ft_print(t_lexer *lx);
char	*ft_substr2(char const *s, unsigned int start, size_t len);
// hello cv | test yarbi hadchi ikhdm
# endif