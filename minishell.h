
#ifndef MINISHELL_H
# define MINISHELL_H


#include "./libft/libfte.h"
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

typedef enum s_token{
   cmd,
   opetion,
   word,
    // Add more node types as needed
} t_token;

typedef struct s_ast
{
    int how_many_cmd;
    char **cmd;
    
    t_token a;
}t_ast;

# endif