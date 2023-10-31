/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:06:31 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/10/31 05:48:22 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./builtins/builtins.h"

void	check_redirections(t_lexer *lexer)
{
	t_lexer	*lexer_p;

	lexer_p = lexer;
	if (!lexer_p)
		return ;
	while (lexer_p->prev)
		lexer_p = lexer_p->prev;
	while (lexer_p != NULL)
	{
		if (lexer_p->token == GREAT
			|| lexer_p->token == GREAT_GREAT)
			overwrite_append(lexer_p);
		else if (lexer_p->token == LESS)
			stdin_redirection(lexer_p);
		else if (lexer_p->token == LESS_LESS)
		{
			dup2(lexer_p->fd[0], STDIN_FILENO);
			close(lexer_p->fd[0]);
			close(lexer_p->fd[1]);
		}
		lexer_p = lexer_p->next;
	}
}

void	build_redirections(t_ast *ast, t_env *env, int	*pipe_fd, int *save)
{
	// int	*doc_pipe;

	t_lexer *lexer = ast->redirections;

	while (lexer)
	{
		heredoc_handler(lexer, env, save);
		lexer = lexer->next;
	}
	if (!ast->prev && ast->next)
		dup2(pipe_fd[1], STDOUT_FILENO);
	else if (ast->prev && ast->next)
	{
		dup2(*save, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
	}
	else if (!ast->next)
		dup2(*save, STDIN_FILENO);
	check_redirections(ast->redirections);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (*save > 0)
		close(*save);
}

void	get_bin_and_exec(t_ast *ast, t_env *env)
{
	char	**bin_paths;
	char	**envp;
	char	*tmp;
	int		i;

	if (env == NULL || ast == NULL)
		return ;
	if (!ast->str || (ast->str && !ast->str[0]))
		return ;
	envp = get_envp(env);
	if (ast->str[0][0] == '.' || ast->str[0][0] == '/')
	{
		if (access(ast->str[0], F_OK | X_OK) != -1)
			execve(ast->str[0], ast->str, envp);
		put_strerror(ast, errno);
		return ;
	}
	i = ((bin_paths = get_bin_paths(env)), -1);
	while (bin_paths[++i])
	{
		tmp = ft_strjoin(bin_paths[i], ast->str[0]);
		if (access(tmp, F_OK | X_OK) != -1)
			execve(tmp, ast->str, envp);
		free(tmp);
	}
	ft_putstr_fd(ast->str[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	(free(bin_paths), free(envp));
}

int	execute_cmd(t_ast *ast, t_env *env)
{
	int		child;
	int		pipe_fd[2];
	static int save;

	// if (ast->redirections != NULL)
	// {
	// 	if (ast->redirections->token == LESS_LESS)
	// 		heredoc_handler(ast->redirections);
	// }
	pipe(pipe_fd);
	child = fork();
	if (child == 0)
	{
		build_redirections(ast, env, pipe_fd, &save);
		if (ast->builtins == 1)
			builtin(child, ast, env);
		else
			get_bin_and_exec(ast, env);
		exit(1);
	}
	else
	{
		if (save > 2)
			close(save);
		save = pipe_fd[0];
		close(pipe_fd[1]);
	}
	return (child);
}

void	execute(t_ast *ast, t_env *env)
{
	int		child;
	int		state;

	child = -1;
	while (ast)
	{
		//Temporary For Test ___________________
		if (ft_strncmp(ast->str[0], "cd", 2) == 0
			|| ft_strncmp(ast->str[0], "pwd", 3) == 0
			|| ft_strncmp(ast->str[0], "exit", 4) == 0
			|| ft_strncmp(ast->str[0], "env", 3) == 0
			|| ft_strncmp(ast->str[0], "export", 6) == 0
			|| ft_strncmp(ast->str[0], "unset", 5) == 0
			|| ft_strncmp(ast->str[0], "echo", 4) == 0)
			ast->builtins = 1;
		//______________________________________
		if (ast->builtins == 1
			&& (!ast->next && !ast->prev && !ast->redirections))
			builtin(child, ast, env);
		else
			child = execute_cmd(ast, env);
		ast = ast->next;
	}
	waitpid(child, &state, 0);
}
