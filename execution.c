/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:06:31 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/10/30 20:58:56 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./builtins/builtins.h"

void	check_redirections(t_lexer *lexer, int *in_fd, t_env *env)
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
			heredoc_handler(lexer_p, in_fd, env);
		lexer_p = lexer_p->next;
	}
}

void	build_redirections(t_ast *ast, int	*pipe_fd, int *save, t_env *env)
{
	//heredoc_handler(ast->redirections, save, env);
	if (!ast->prev && ast->next)
		dup2(pipe_fd[1], STDOUT_FILENO);
	else if (ast->prev && ast->next)
	{
		dup2(*save, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
	}
	else if (!ast->next)
		dup2(*save, STDIN_FILENO);
	check_redirections(ast->redirections, save, env);
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
		build_redirections(ast, pipe_fd, &save, env);
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

//hna ghadi tready ga3  herdoc li kainin o t save fd  dyalhom o dik sa3a finma l9iti commend m7taja input dyal herdoc rah ghadi tkhedm ghir f fd li endk fih data 
// i try to give my best to fix what i can nta db ghadi t3erf ach khasso itdar
void read_heardoc(t_ast *cmds, t_env* env)
{
	t_ast *head;
	t_lexer *head_r;
	pid_t pid;
	int status;
	int pip[2];
	
	head = cmds;
	while(head)
	{
		head_r = head->redirections;
		while(head_r && head_r->token == LESS_LESS)
		{
			if (pipe(pip) == -1)
				return ;
			pid = fork();
			if (pid == -1)
				return ;
			if (pid == 0)
			{
				close(pip[0]);
				while (1)
				{
					head_r->doc_data = readline("heredoc> ");
					if (!head_r->doc_data
						|| ft_memcmp(head_r->doc_data, head_r->word, ft_strlen(head_r->word) + 1) == 0)
						break ;
					if(head_r->q == 0)
						expand_herdoc(head_r, env);
					ft_putstr_fd(head_r->doc_data, pip[1]);
					ft_putchar_fd('\n', pip[1]);
					free(head_r->doc_data);
				}
				close(pip[1]);
				exit(0);
			}
			close(pip[1]);
			waitpid(pid, &status, 0);
			head_r->fd = pip[0];
			head_r = head_r->next;
		}
		head = head->next;
	}
}

void	execute(t_ast *ast, t_env *env)
{
	int		child;
	int		state;

	child = -1;
	//read_heardoc(ast, env); 9ra comment li kain lfog bach t3erf ach kain
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
