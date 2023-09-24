/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:06:31 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/09/24 00:48:17 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./builtins/builtins.h"

char	**get_bin_paths(t_env *env)
{
	int		i;
	char	**ret;
	char	*tmp;
	t_env	*env_p;

	env_p = get_env_var(env, "PATH");
	if (env_p != NULL)
		ret = ft_split(env_p->value, ':');
	i = -1;
	while (ret[++i])
	{
		if (ret[i][ft_strlen(ret[i]) - 1] != '/')
		{
			tmp = ft_strjoin(ret[i], "/");
			free(ret[i]);
			ret[i] = ft_strdup(tmp);
			free(tmp);
		}
	}
	return (ret);
}

// void	set_redirections(t_lexer *lexer, int *pipe_fd)
// {
// 	int		fd;
// 	t_lexer	*lex;

// 	lex = lexer;
// 	while (lex)
// 	{
// 		if (lex->token == PIPE)
// 	}
// }

void	check_redirections(t_lexer *lexer, int *fds)
{
	int	i;
	t_lexer	*lexer_p;
	
	lexer_p = lexer;
	while (lexer_p != NULL)
	{
		if (lexer_p->token == GREAT)
			great(lexer_p, fds);
		lexer_p = lexer_p->next;
	}
	
}

int	execute_cmd(t_ast *ast, t_env *env)
{
	int		child;
	int		i, pipe_fd[2];
	char	**bin_paths;
	char	*tmp;
	static int save;

	pipe(pipe_fd);

	// if (ast == NULL)
	// 	return 0;
	// if (ast->prev != NULL)
	// {
	// 	// dup2(pipe_fd[0], STDIN_FILENO);
	// 	// close(pipe_fd[1]);
	// 	close(pipe_fd[1]);
	// }
	child = fork();
	if (child == 0)
	{
		// getchar();
		// if (ast->next != NULL /*|| (ast->redirections != NULL
		// 	&& ast->redirections->token == GREAT)*/)
		// {
		// 	close(pipe_fd[0]);
		// 	dup2(pipe_fd[1], STDOUT_FILENO);
		// 	close(pipe_fd[1]);
		// }
		// else if (ast->prev != NULL)
		// {
		// 	close(pipe_fd[1]);
		// 	dup2(pipe_fd[0], STDIN_FILENO);
		// 	close(pipe_fd[0]);
		// }

		if (!ast->prev) {
			dup2(pipe_fd[1], 1);
		}
		else if (ast->prev && ast->next)
		{
			dup2(save, 0);
			dup2(pipe_fd[1], 1);
		}
		else if (!ast->next) {
			dup2(save, 0);
		}
		
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(save);
		bin_paths = get_bin_paths(env);
		i = -1;
		while (bin_paths[++i])
		{
			tmp = ft_strjoin(bin_paths[i], ast->str[0]);
			execve(tmp, ast->str, NULL);
			// perror("execve()");
		}
	}
	else
	{
		if (save > 2)
			close(save);
		save = pipe_fd[0];
		close(pipe_fd[1]);
		// check_redirections(ast->redirections, pipe_fd);
		return child;
	}
}

void	execute(t_ast *ast, t_env *env)
{
	t_ast	*ast_p;
	int		child;
	int		state;
	// int		pipe_fd[2];

	
	ast_p = ast;
	while (ast_p)
	{	
		// if (ast->builtins != 0)
		// 	builtin(ast, env);
		// else
		// if (ast_p->redirections != NULL)
		// 	check_redirections(ast_p->redirections);
			
			child = execute_cmd(ast_p, env);
		// if (child != 0)
		// 	waitpid(child, &state ,0);
		ast_p = ast_p->next;
	}
	// waitpid(child, &state ,0);
	// close (pipe_fd[1]);
	// close (pipe_fd[0]);
}