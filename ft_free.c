/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 11:52:33 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/10/23 19:13:40 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_token(t_lexer *lx)
{
	while (lx && lx->prev)
		lx = lx->prev;
	while (lx && lx->next)
	{
		if (lx->word)
			free(lx->word);
		if (lx->prev)
			free(lx->prev);
		lx = lx->next;
	}
	if (lx && lx->prev)
		free(lx->prev);
	if (lx)
		free(lx);
}

void	ft_free_ast(t_ast *tool)
{
	t_ast	*replace;

	while (tool->prev)
		tool = tool->prev;
	ft_free_token(tool->token);
	while (tool)
	{
		if (tool->str)
			free(tool->str);
		while (tool->redirections && tool->redirections->prev)
			tool->redirections = tool->redirections->prev;
		while (tool->redirections)
		{
			tool->token = tool->redirections;
			tool->redirections = tool->redirections->next;
			free(tool->token);
		}
		if (tool->redirections)
			free(tool->redirections);
		replace = tool;
		tool = tool->next;
		free(replace);
	}
	free(tool);
}
