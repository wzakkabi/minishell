/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:55:42 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/11/02 22:53:25 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_w_acc(char *file)
{
	if (access(file, W_OK) != 0)
	{
		if (errno != ENOENT)
		{
			perror(file);
			return (0);
		}
	}
	return (1);
}

int	overwrite_append(t_lexer *lexer)
{
	int	fd;

	fd = -1;
	if (lexer == NULL)
		return (1);
	if (lexer && lexer->word == NULL)
		return (0);
	if (!check_w_acc(lexer->word))
		return (0);
	if (lexer->token == GREAT)
		fd = open(lexer->word, O_CREAT | O_TRUNC | O_WRONLY,
				S_IRUSR | S_IWUSR);
	else if (lexer->token == GREAT_GREAT)
		fd = open(lexer->word, O_CREAT | O_APPEND | O_WRONLY,
				S_IRUSR | S_IWUSR);
	if (fd <= 2)
		return (0);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	stdin_redirection(t_lexer *lexer)
{
	int	fd;

	fd = -1;
	if (lexer == NULL || (lexer && lexer->word == NULL))
		return (0);
	if (access(lexer->word, F_OK | R_OK) != 0)
	{
		perror(lexer->word);
		return (0);
	}
	if (lexer->token == LESS)
		fd = open(lexer->word, O_RDONLY);
	if (fd <= 2)
		return (0);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

void	heredoc_hendler(t_ast *ast, t_env *env)
{
	t_lexer	*lexer;

	doc_signal();
	while (ast)
	{
		lexer = ast->redirections;
		while (lexer)
		{
			if (lexer->token == LESS_LESS)
				get_doc_data(lexer, env);
			if (g_signo == 1)
				free_doc_data(lexer);
			lexer = lexer->next;
		}
		ast = ast->next;
	}
}

void	get_doc_data(t_lexer *lexer, t_env *env)
{
	char	*tmp;
	char	*tmp2;

	while (1)
	{
		if (g_signo == 1)
			break ;
		tmp = readline("heredoc> ");
		if (!tmp
			|| !ft_strncmp(lexer->word, tmp, ft_strlen(lexer->word) + 1))
		{
			free(tmp);
			break ;
		}
		if (!lexer->doc_data)
			lexer->doc_data = ft_strjoin(tmp, "\n");
		else
		{
			tmp2 = ft_strjoin(lexer->doc_data, tmp);
			free(lexer->doc_data);
			lexer->doc_data = ft_strjoin(tmp2, "\n");
			free(tmp2);
		}
		free(tmp);
	}
	if (!lexer->q)
		expand_herdoc(lexer, env);
}
