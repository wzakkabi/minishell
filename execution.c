/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:06:31 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/10/16 19:09:31 by mbousbaa         ###   ########.fr       */
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

void	check_redirections(t_lexer *lexer, int *fds)
{
	int	i;
	t_lexer	*lexer_p;
	
	lexer_p = lexer;
	while (lexer_p != NULL)
	{
		if (lexer_p->token == GREAT
			|| lexer_p->token == GREAT_GREAT)
			overwrite_append(lexer_p, fds);
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
	// check_redirections(ast->redirections, pipe_fd);
	child = fork();
	if (child == 0)
	{
	check_redirections(ast->redirections, pipe_fd);
		if (!ast->prev && ast->next && !ast->redirections) {
			dup2(pipe_fd[1], STDOUT_FILENO);
		}
		else if (ast->prev && ast->next)
		{
			dup2(save, STDIN_FILENO);
			dup2(pipe_fd[1], STDOUT_FILENO);
		}
		else if (!ast->next) {
			dup2(save, STDIN_FILENO);
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
		}
	}
	else
	{
		if (save > 2)
			close(save);
		save = pipe_fd[0];
		close(pipe_fd[1]);
	}
	return child;
}

void	execute(t_ast *ast, t_env *env)
{
	t_ast	*ast_p;
	int		child;
	int		state;
	
	ast_p = ast;
	while (ast_p)
	{	
		// if (ast->builtins != 0)
		// 	builtin(ast, env);
		// else
			child = execute_cmd(ast_p, env);
		// if (child != 0)
		// 	waitpid(child, &state ,0);
		ast_p = ast_p->next;
	}
	waitpid(child, &state ,0);
	// close (pipe_fd[1]);
	// close (pipe_fd[0]);
}