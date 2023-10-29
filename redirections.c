/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:55:42 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/10/29 09:50:01 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	overwrite_append(t_lexer *lexer)
{
	int	fd;

	fd = -1;
	if (lexer == NULL)
		return ;
	if ((lexer->token != GREAT && lexer->token != GREAT_GREAT)
		|| lexer->word == NULL)
		return ;
	// Needs to add permission check before trying to open the file
	// Or handle it from open() ret values
	if (lexer->token == GREAT)
		fd = open(lexer->word, O_CREAT | O_TRUNC | O_WRONLY,
			S_IRUSR | S_IWUSR);
	else if (lexer->token == GREAT_GREAT)
		fd = open(lexer->word, O_CREAT | O_APPEND | O_WRONLY,
				S_IRUSR | S_IWUSR);
	// Bad file descriptor errors needs to be handled
	if (fd <= 2)
		return ;
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	stdin_redirection(t_lexer *lexer)
{
	int	fd;

	fd = -1;
	if (lexer == NULL)
		return ;
	if ((lexer->token != LESS)
		|| lexer->word == NULL)
		return ;
	// Needs to add permission check before trying to open the file
	// Or handle it from open() ret values
	if (lexer->token == LESS)
		fd = open(lexer->word, O_RDONLY);
	// Bad file descriptor errors needs to be handled
	if (fd <= 2)
		return ;
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	putstr_expanded(int str, int start, int end, char *env_val)
{
	
}

char	*expand_heredoc(char *str)
{
	int		i;
	int		start;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i++] == '$')
	{
		if (ft_isalpha(str[i]) && str[i] == '_')
		{
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			if (str[i] == ' ' || (!ft_isalnum(str[i]) && str[i] != '_'))
				tmp = ft_substr(str, start, i);
			if (!tmp)
				return ;
			// need replace the extracted env var & print it or return it
			//putstr_expanded()
		}
	}
	
}

int	*heredoc_handler(t_lexer *lexer, int *in_fd)
{
	char	*tmp;
	int		*doc_pipe;

	doc_pipe = malloc(sizeof(int) * 2);
	if (lexer && lexer->token == LESS_LESS)
	{
		pipe(doc_pipe);
		while (1)
		{
			tmp = readline("heredoc> ");
			if (!tmp
				|| ft_memcmp(tmp, lexer->word, ft_strlen(lexer->word) + 1) == 0)
				break ;
			if (lexer->q)
				expand_heredoc(tmp);
			ft_putstr_fd(tmp, doc_pipe[1]);
			ft_putchar_fd('\n', doc_pipe[1]);
			free(tmp);
		}
	}
	return (doc_pipe);
}
