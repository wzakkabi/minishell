/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:10:20 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/10/31 01:24:22 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <termcap.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

typedef enum s_token
{
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
	PIPE,
}	t_token;

typedef struct s_lexer
{
	int				*fd; // hada howa li fin kain file discripte le ghadi t7tage input li fih 
	char			*word;
	t_token			token;
	int				num_node;
	int				q;
	struct s_lexer	*next;
	struct s_lexer	*prev;
	char	*doc_data;
}	t_lexer;

// int builtins = 0 false o 1 true
//t_lexer	*redirections; = here is all the node of redirection
//t_lexer	*token = i add it just to free all in one move
// str all the commend and paramiter
typedef struct s_ast
{
	char			**str;
	int				builtins;
	t_lexer			*redirections;
	t_lexer			*token;
	struct s_ast	*next;
	struct s_ast	*prev;
}	t_ast;

//int print_or_not; //0 or 1 ztha  bach n3erfha wach n9dero nprantiwha ola la
typedef struct s_env 
{
	char			*key;
	char			*value;
	int				print_or_not;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

// minishell.c
void	minishell_loop(t_env *env);
int		main(int c, char **av, char **grep_env);

/**** exit_status ****/
void	ft_exit(t_env *env, int return_status);

// create_node.c
t_ast	*newnode(void);
t_lexer	*lxnewnode(void);
t_env	*envnode(void);

// expand.c
void	check_expand(t_lexer *token, t_env *env);

// ft_substr2.c
char	*ft_substr2(char const *s, unsigned int start, size_t len);
int		ft_strncmp2(const char *s1, const char *s2, size_t n);

// ft_token.c
t_lexer	*ft_token(char *ret);

// signal.c
void	ft_signal(void);

//	split_to_ast_node.c
t_ast	*split_to_ast(t_lexer *lx);
void	remove_qost(t_lexer *token, int x, int y, int qst);
void	make_env_node(char **env, t_env *node);

// syntax_error.c
int		check_quote(char *str, t_env *env, int y);
int		check_syntax_error(t_env *env, t_lexer *err);
int		check_syntax_error_again(t_ast *tool);

// ft_free.c
void	ft_free_token(t_lexer *lx);
void	ft_free_ast(t_ast *tool);

// new readline
void	rl_replace_line(const char *text, int clear_undo);

//  execution.c
void	execute(t_ast *ast, t_env *env);

// redirections.c
// void	overwrite_append(t_lexer *lexer, int *pipe_fds);
void	overwrite_append(t_lexer *lexer);
void	stdin_redirection(t_lexer *lexer);
void	heredoc_handler(t_lexer *lexer, t_env *env, int *in_fd);

// execution2.c
void	put_strerror(t_ast *ast, int __errno);
char	**get_bin_paths(t_env *env);
char	**get_envp(t_env *env);
void	builtin(int child, t_ast *ast, t_env *env);

//epand_heredoc.c
void	read_heardoc(t_ast *cmds, t_env* env);
void	expand_herdoc(t_lexer *token, t_env *env);
#endif
