
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
	t_lexer					*token;
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

// new readline
void rl_replace_line(const char *text, int clear_undo);

//create_node
t_ast	*newnode(void);
t_lexer	*lxnewnode(void);
t_env	*envnode(void);

//error
int		check_quote(char *str);
void	check_syntax_error(t_lexer *err);
int		check_syntax_error_again(t_ast *tool);

//expand
void    check_expand(t_lexer *token, t_env *env);

//split_to_ast
t_ast	*split_to_ast(t_lexer *lx);
void	remove_qost(t_lexer *token, int x, int y, int qst);

void	ft_print(t_lexer *lx);
t_lexer	*ft_token(char *ret);
char	*ft_substr2(char const *s, unsigned int start, size_t len);

// execution.c
void	execute(t_ast *ast, t_env *env);

// redirections.c
void	overwrite_append(t_lexer *lexer, int *pipe_fds);

# endif