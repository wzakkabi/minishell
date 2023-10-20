/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:06:31 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/10/19 22:14:45 by mbousbaa         ###   ########.fr       */
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

	if (!env)
		return (NULL);
	env_p = get_env_var(env, "PATH");
	if (!env_p)
		return (NULL);
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

void	builtin(int child, t_ast *ast, t_env *env)
{
	if ( ft_strncmp(ast->str[0], "cd", 2) == 0)
		cd(ast, env);
	else if (ft_strncmp(ast->str[0], "pwd", 3) == 0)
		pwd(ast);
	else if (ft_strncmp(ast->str[0], "exit", 4) == 0)
		builtin_exit(ast);
	else if (ft_strncmp(ast->str[0], "env", 3) == 0)
		builtin_env(env);
	else if (ft_strncmp(ast->str[0], "export", 6) == 0)
		export(ast, env);
	else if (ft_strncmp(ast->str[0], "unset", 5) == 0)
		unset(ast, env);
	else if (ft_strncmp(ast->str[0], "echo", 4) == 0)
		echo(ast, env);
	if (child == 0)
		exit(0);
}

void	check_redirections(t_lexer *lexer)
{
	t_lexer	*lexer_p;

	lexer_p = lexer;
	while (lexer_p != NULL)
	{
		if (lexer_p->token == GREAT
			|| lexer_p->token == GREAT_GREAT)
			overwrite_append(lexer_p);
		lexer_p = lexer_p->next;
	}
}

void	build_redirections(t_ast *ast, int	*pipe_fd, int *save)
{
	check_redirections(ast->redirections);
	if (!ast->prev && ast->next && !ast->redirections)
		dup2(pipe_fd[1], STDOUT_FILENO);
	else if (ast->prev && ast->next)
	{
		dup2(*save, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
	}
	else if (!ast->next)
		dup2(*save, STDIN_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(*save);
}

void	get_bin_and_exec(t_ast *ast, t_env *env)
{
	char	**bin_paths;
	char	*tmp;
	int		i;

	bin_paths = get_bin_paths(env);
	i = -1;
	while (bin_paths[++i])
	{
		tmp = ft_strjoin(bin_paths[i], ast->str[0]);
		if (access(tmp, F_OK | X_OK) != -1)
			execve(tmp, ast->str, NULL);
		free(tmp);
	}
	ft_putstr_fd(ast->str[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	free(bin_paths);
}

int	execute_cmd(t_ast *ast, t_env *env)
{
	int		child;
	int		pipe_fd[2];
	static int save;

	pipe(pipe_fd);
	child = fork();
	if (child == 0)
	{
		build_redirections(ast, pipe_fd, &save);
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
		{
			builtin(child, ast, env);
		}
		else
			child = execute_cmd(ast, env);
		ast = ast->next;
	}
	waitpid(child, &state, 0);
}
