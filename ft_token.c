/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 01:49:58 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/11/03 11:58:35 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_vr_ft_token
{
	int		cnt;
	t_lexer	*lx;
	t_lexer	*head;
	char	*p;
	int		y;
	int		test;
	int		qst;
}t_vr_ft_token;

int	token_or_not(char c, char c1)
{
	if (c == '<' && c1 == '<')
		return (3);
	else if (c == '>' && c1 == '>')
		return (1);
	else if (c == '<')
		return (2);
	else if (c == '>')
		return (0);
	else if (c == '|')
		return (4);
	return (6);
}

t_lexer	*creat_node_token(char c, char c1, t_lexer *lx)
{
	t_token	test;

	test = -6;
	if (c == '<' && c1 == '<')
		test = LESS_LESS;
	else if (c == '>' && c1 == '>')
		test = GREAT_GREAT;
	else if (c == '<')
		test = LESS;
	else if (c == '>')
		test = GREAT;
	else if (c == '|')
		test = PIPE;
	lx->token = test;
	lx->word = NULL;
	lx->next = lxnewnode();
	lx->next->prev = lx;
	return (lx->next);
}

t_lexer	*creat_node_word(t_lexer *lx, char *ret, int y, int cnt)
{
	char	*tmp;

	if (y == cnt)
		return (lx);
	lx->token = -1;
	if (lx->prev && lx->prev->token == LESS_LESS)
	{
		tmp = ft_substr2(ret, y, cnt);
		lx->word = ft_strjoin(tmp, "\n");
		free(tmp);
	}
	else
		lx->word = ft_substr2(ret, y, cnt);

	lx->next = lxnewnode();
	lx->next->prev = lx;
	return (lx->next);
}

void	ft_token_helper(t_vr_ft_token *t, char *ret, int if_redirection)
{
	if (if_redirection == 0)
	{
		t->test = ((t->qst = ret[t->cnt]), (t->cnt++), t->cnt);
		while (ret[t->cnt] != t->qst && ret[t->cnt])
			t->cnt++;
		if (ret[++t->cnt] == 0)
			t->lx = creat_node_word(t->lx, ret, t->y, t->cnt);
	}
	else if (if_redirection == 1)
	{
		if (t->y != t->cnt)
			t->lx = creat_node_word(t->lx, ret, t->y, t->cnt);
		t->lx = creat_node_token(ret[t->cnt], ret[t->cnt + 1], t->lx);
		if (t->test == 1 || t->test == 3)
			t->cnt += 1;
		t->y = ++t->cnt;
	}
	else
	{
		t->lx = creat_node_word(t->lx, ret, t->y, t->cnt);
		while ((ret[t->cnt] && ret[t->cnt] == ' ')
			|| (ret[t->cnt] && ret[t->cnt] == '\t')
			|| (ret[t->cnt] && ret[t->cnt] == '\n'))
			t->cnt++;
	}
}

t_lexer	*ft_token(char *ret)
{
	t_vr_ft_token	*t;
	t_lexer			*head;

	t = (t_vr_ft_token *)malloc(sizeof(t_vr_ft_token));
	t->cnt = ((t->y = 0), (t->lx = lxnewnode()), (head = t->lx), 0);
	while (ret[t->cnt])
	{
		t->test = token_or_not(ret[t->cnt], ret[t->cnt + 1]);
		if (ret[t->cnt] == 34 || ret[t->cnt] == 39)
			ft_token_helper(t, ret, 0);
		else if (t->test == 0 || t->test == 1
			|| t->test == 2 || t->test == 3 || t->test == 4)
			ft_token_helper(t, ret, 1);
		else if (ret[t->cnt] == ' ' || ret[t->cnt] == '\t'
			|| ret[t->cnt] == '\n')
			t->y = ((ft_token_helper(t, ret, 2)), t->cnt);
		else
		{
			if ((ret[++t->cnt] == 0 && ret[t->cnt - 1] != ' ')
				&& (ret[t->cnt] == 0 && ret[t->cnt - 1] != '\t'))
				t->lx = creat_node_word(t->lx, ret, t->y, t->cnt);
		}
	}
	free(t);
	return (head);
}
