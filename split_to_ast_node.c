/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_ast_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 00:28:48 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/10/18 04:44:02 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ast_helper(t_lexer *lx, t_ast *tool, int *cnt)
{
	if (lx->token == GREAT || lx->token == GREAT_GREAT
		|| lx->token == LESS || lx->token == LESS_LESS)
	{
		if (tool->redirections == NULL)
			tool->redirections = lxnewnode();
		else
		{
			tool->redirections->next = lxnewnode();
			tool->redirections->next->prev = tool->redirections;
			tool->redirections = tool->redirections->next;
		}
		tool->redirections->token = lx->token;
		lx = lx->next;
		tool->redirections->word = lx->word;
	}
	else if (lx->word != NULL)
	{
		tool->str[*cnt] = lx->word;
		*cnt += 1;
	}
}

t_ast	*split_to_ast(t_lexer *lx)
{
	t_ast	*tool_head;
	t_ast	*tool;
	int		cnt;

	tool = ((cnt = 0), newnode());
	tool_head = tool;
	tool->redirections = NULL;
	while (lx->next != NULL)
	{
		if (lx->token == PIPE)
		{
			tool->next = newnode();
			tool->next->prev = tool;
			tool = tool->next;
			cnt = 0;
			tool->redirections = NULL;
		}
		ast_helper(lx, tool, &cnt);
		lx = lx->next;
	}
	return (tool_head);
}

void	remove_qost(t_lexer *token, int x, int y, int qst)
{
	char	*new_word;

	while (token->next)
	{
		x = ((y = -1), -1);
		while (token->word && token->word[++x])
		{
			if (token->word[x] == 34 || token->word[x] == 39)
			{
				qst = token->word[x];
				new_word = malloc(ft_strlen(token->word) - 2 + 1);
				while (++y < x)
					new_word[y] = token->word[y];
				x++;
				while (token->word[x] && token->word[x] != qst)
					new_word[y++] = token->word[x++];
				qst = ((x++), 0);
				while (token->word[x + qst])
					new_word[y++] = token->word[x + qst++];
				new_word[y] = ((free(token->word)), 0);
				y = ((token->word = new_word), (x = x - 3), -1);
			}
		}
		token = token->next;
	}
}
