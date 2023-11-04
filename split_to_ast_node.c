/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_ast_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 00:28:48 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/11/04 11:31:33 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reset_to_0(t_ast *tool, t_lexer *lx, int	*cnt, int tx)
{
	char	**p;

	if (tx == 0)
	{
		while (tool && tool->prev)
			tool = tool->prev;
		while (tool)
		{
			while (tool->redirections && tool->redirections->prev)
				tool->redirections = tool->redirections->prev;
			tool = tool->next;
		}
	}
	else if (tx == 1)
	{
		if (lx->q == 0)
		{
			tx = ((p = ft_split(lx->word, ' ')), 0);
			while (p[tx])
				*cnt = ((tool->str[*cnt] = ft_substr2(p[tx],
								0, ft_strlen(p[tx]))), (tx++), (*cnt + 1));
			ft_free_2darry(p);
		}
	}
}

t_lexer	*ast_helper(t_lexer *lx, t_ast *tool, int *cnt)
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
		tool->redirections->q = lx->q;
		tool->redirections->word = lx->word;
	}
	else if (lx->word != NULL)
	{
		ft_reset_to_0(tool, lx, cnt, 1);
		if (lx->q == 1)
			*cnt = (tool->str[*cnt] = ft_substr2(lx->word, 0,
						ft_strlen(lx->word)), *cnt + 1);
	}
	return (lx->next);
}

t_ast	*split_to_ast(t_lexer *lx)
{
	t_ast	*tool_head;
	t_ast	*tool;
	int		cnt;

	tool = ((cnt = 0), newnode());
	tool_head = tool;
	tool->redirections = NULL;
	tool->token = lx;
	while (lx && lx->next != NULL)
	{
		if (lx->token == PIPE)
		{
			tool->next = newnode();
			tool->next->prev = tool;
			tool = tool->next;
			cnt = 0;
			tool->redirections = NULL;
		}
		lx = ast_helper(lx, tool, &cnt);
	}
	ft_reset_to_0(tool, lx, &cnt, 0);
	return (tool_head);
}

void	remove_qost(t_lexer *token, int x, int y, int qst)
{
	char	*new_word;

	while (token->next)
	{
		x = ((y = -1), (token->q = 0), -1);
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
				y = ((token->word = new_word), (x = x - 3), (token->q = 1), -1);
			}
		}
		token = token->next;
	}
}

void	make_env_node(char **env, t_env *node)
{
	int	cnt_x;
	int	cnt_y;

	cnt_y = ((cnt_x = 0), 0);
	while (env[cnt_y])
	{
		while (env[cnt_y][cnt_x] != '=' && env[cnt_y][cnt_x])
			cnt_x++;
		node->key = ft_substr2(env[cnt_y], 0, cnt_x);
		node->value = ft_substr2(env[cnt_y], cnt_x + 1, ft_strlen(env[cnt_y]));
		node->print_or_not = 1;
		cnt_x = 0;
		cnt_y++;
		node->next = envnode();
		node->next->prev = node;
		node = node->next;
	}
	node->key = ft_substr("?", 0, 1);
	node->value = ft_itoa(0);
	node->print_or_not = 0;
}
