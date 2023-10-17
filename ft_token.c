/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 01:49:58 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/10/17 01:52:02 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_vr_ft_token
{
	int		cnt;
	t_lexer	*lx;
	char	*p;
	int		y;
	int		test;
	int		qst;
}t_vr_ft_token;

int	token_or_not(char c, char c1)
{
	if (c == '<' && c1 == '<')
		return (0);
	else if (c == '>' && c1 == '>')
		return (1);
	else if (c == '<')
		return (2);
	else if (c == '>')
		return (3);
	else if (c == '|')
		return (4);
	return (6);
}

t_lexer	*creat_node_token(char c, char c1, t_lexer *lx)
{
	t_token	test;

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
	if (y == cnt)
		return (lx);
	lx->token = -1;
	lx->word = ft_substr2(ret, y, cnt);
	lx->next = lxnewnode();
	lx->next->prev = lx;
	return (lx->next);
}

void	ft_token_helper_qst(t_vr_ft_token *t, char *ret)
{
	t->test = ((t->qst = ret[t->cnt]), (t->cnt++), t->cnt);
	while (ret[t->cnt] != t->qst && ret[t->cnt])
		t->cnt++;
	if (ret[++t->cnt] == 0)
		t->lx = creat_node_word(t->lx, ret, t->y, t->cnt);
}

void	ft_token_redirection(t_vr_ft_token *t, char *ret)
{
	t->lx = creat_node_token(ret[t->cnt], ret[t->cnt + 1], t->lx);
	if (t->test == 0 || t->test == 1)
		t->cnt += 2;
	else
		t->cnt++;
	t->y = t->cnt;
}

t_lexer	*ft_token(char *ret)
{
	t_vr_ft_token	t;

	t.cnt = ((t.y = 0), (t.lx = lxnewnode()), 0);
	while (ret[t.cnt])
	{
		t.test = token_or_not(ret[t.cnt], ret[t.cnt + 1]);
		if (ret[t.cnt] == 34 || ret[t.cnt] == 39)
			ft_token_helper_qst(&t, ret);
		else if (t.test == 0 || t.test == 1
			|| t.test == 2 || t.test == 3 || t.test == 4)
			ft_token_redirection(&t, ret);
		else if (ret[t.cnt] == ' ' || ret[t.cnt] == '\t')
		{
			t.lx = creat_node_word(t.lx, ret, t.y, t.cnt);
			t.y = (t.cnt++, t.cnt);
		}
		else
		{
			t.cnt++;
			if ((ret[t.cnt] == 0 && ret[t.cnt - 1] != ' ')
				&& (ret[t.cnt] == 0 && ret[t.cnt - 1] != '\t'))
				t.lx = creat_node_word(t.lx, ret, t.y, t.cnt);
		}
	}
	return (t.lx);
}