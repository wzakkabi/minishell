/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:55:42 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/09/24 23:38:51 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	great(t_lexer *lexer, int *pipe_fds)
{
	int 	fd;
	int		count;
	char	buff[BUFSIZ];

	if (lexer == NULL)
		return ;
	if (lexer->token != GREAT || lexer->word == NULL)
		return ;
	fd = open(lexer->word, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	if (fd <= 2)
		return ;
	// close(pipe_fds[1]);
	// count = read(pipe_fds[0], buff, BUFSIZ);
	// close(pipe_fds[0]);
	// if (count > 0)
	// {
	// 	// buff[count] = '\0';
	// 	int w_ret = write(fd, buff, count);
	// 	if (w_ret <= 0)
	// 		perror("write()");
			
	// }
	dup2(fd, STDOUT_FILENO);
	close(fd);
}