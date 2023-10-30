/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:55:42 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/10/30 20:15:44 by wzakkabi         ###   ########.fr       */
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

void	heredoc_handler(t_lexer *lexer, int *in_fd, t_env *env)
{
	//char	*tmp;
	int		tmp_p[2];
	
	//db expand mgad but tertib dyalhadchi khasso itgad
	if (lexer && lexer->token == LESS_LESS)
	{
		pipe(tmp_p);
		while (1)
		{
			lexer->doc_data = readline("heredoc> ");
			if (!lexer->doc_data
				|| ft_memcmp(lexer->doc_data, lexer->word, ft_strlen(lexer->word) + 1) == 0)
				break ;
			if(lexer->q == 0)
				expand_herdoc(lexer, env);
			ft_putstr_fd(lexer->doc_data, tmp_p[1]);
			ft_putchar_fd('\n', tmp_p[1]);
			free(lexer->doc_data);
		}
		dup2(tmp_p[0], *in_fd);
		close(tmp_p[0]);
		close(tmp_p[1]);
	} 
}

// function assliya
// void	heredoc_handler(t_lexer *lexer, int *in_fd, t_env *env)
// {
// 	//char	*tmp;
// 	int		tmp_p[2];
	
// 	//db expand mgad but tertib dyalhadchi khasso itgad
// 	if (lexer && lexer->token == LESS_LESS)
// 	{
// 		pipe(tmp_p);
// 		while (1)
// 		{
// 			lexer->doc_data = readline("heredoc> ");
// 			if (!lexer->doc_data
// 				|| ft_memcmp(lexer->doc_data, lexer->word, ft_strlen(lexer->word) + 1) == 0)
// 				break ;
// 			if(lexer->q == 0)
// 				expand_herdoc(lexer, env);
// 			ft_putstr_fd(lexer->doc_data, tmp_p[1]);
// 			ft_putchar_fd('\n', tmp_p[1]);
// 			free(lexer->doc_data);
// 		}
// 		dup2(tmp_p[0], *in_fd);
// 		close(tmp_p[0]);
// 		close(tmp_p[1]);
// 	} 
// }
