/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:06:31 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/10/22 08:33:46 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./builtins/builtins.h"

void	check_redirections(t_lexer *lexer)
{
	t_lexer	*lexer_p;

	lexer_p = lexer;
	while (lexer_p != NULL)
	{
		if (lexer_p->token == GREAT
			|| lexer_p->token == GREAT_GREAT)
			overwrite_append(lexer_p);
		// if (lexer_p->token == LESS_LESS)
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
	if (ast->redirections != NULL)
	{
		t_lexer	*lex = ast->redirections;
		if (lex->token == LESS_LESS)
			write(*save, lex->doc_data, ft_strlen(lex->doc_data));
		if (lex->token == LESS)
		{
			int file_fd = open(lex->word, O_RDONLY);
			dup2(file_fd, STDIN_FILENO);
			close(file_fd);
		}
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(*save);
}

void	get_bin_and_exec(t_ast *ast, t_env *env)
{
	char	**bin_paths;
	char	**envp;
	char	*tmp;
	int		i;

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

	t_lexer *lexer_p = ast->redirections;
	pipe(pipe_fd);
	if (lexer_p && lexer_p->token == LESS_LESS)
	{
		char	*tmp;
		char	*holder = NULL;
		int		last;

		while (1)
		{
			if (holder)
				holder = ft_strjoin(holder, "\n");
			tmp = readline("heredoc> ");
			if (!tmp || ft_memcmp(tmp, lexer_p->word,
					ft_strlen(lexer_p->word) + 1) == 0)
				break ;
			if (holder == NULL)
				holder = ft_strdup(tmp);
			else
				holder = ft_strjoin(holder, tmp);
		}
		lexer_p->doc_data = holder;
		// printf("%s\n", holder);
		// dup2(pipe_fd[1], STDOUT_FILENO);
		// close(pipe_fd[1]);
		// write(pipe_fd[1], holder, ft_strlen(holder));
	}
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
			builtin(child, ast, env);
		else
			child = execute_cmd(ast, env);
		ast = ast->next;
	}
	waitpid(child, &state, 0);
}
