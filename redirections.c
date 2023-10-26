/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:55:42 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/10/26 03:25:48 by mbousbaa         ###   ########.fr       */
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
		fd = open(lexer->word, O_CREAT | O_APPEND | O_WRONLY | O_APPEND,
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
