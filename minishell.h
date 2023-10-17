
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
#include <sys/wait.h>

typedef struct s_expand
{
	int		x;
	int		y;
	int		i;
	int		dollar;
	int		c_p_dollar;
	int		c_p_key;
	char	*key;
	char	*new_word;
}t_ex;

typedef enum s_token
{
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
	PIPE,
} t_token;

typedef struct s_lexer
{
	char    	*word;
	t_token       token;
	int			num_node;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;


typedef struct s_ast
{
	char                    **str;
	int						builtins; // 0 false o 1 true >> hadi ila kant t_ast fiha cmd li galo lina dero
	t_lexer                 *redirections;/*hna ghadi ndir lik ga3 node li fihom redirection b tertib bhal >> > << <
	ghadi ikom token = "redirection" and word fiha ya ima delemter or smit file */
	struct s_ast			*next;
	struct s_ast			*prev;
} t_ast;


typedef struct s_env 
{
	char *key;
	char *value;
	struct s_env *next;
	struct s_env *prev;
} t_env;

t_ast	*newnode(void);
t_lexer	*lxnewnode(void);


void ft_print(t_lexer *lx);
t_lexer	*ft_token(char *ret);
char	*ft_substr2(char const *s, unsigned int start, size_t len);

// execution.c
void	execute(t_ast *ast, t_env *env);

// redirections.c
void	overwrite_append(t_lexer *lexer, int *pipe_fds);

# endif