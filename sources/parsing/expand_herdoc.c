/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:20:15 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/11/04 16:31:23 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../builtins/builtins.h"

typedef struct s_expand
{
	int		x;
	int		y;
	int		i;
	int		dollar;
	int		c_p_dollar;
	int		pk;
	char	*key;
	char	*new_word;
}t_ex;

int	how_many_dollar(char *s, int c)
{
	int	x;
	int	find;

	x = ((find = 0), -1);
	while (s && s[++x])
	{
		if (s[x] == c && s[x + 1] != 0)
			find++;
	}
	return (find);
}

void	helper_1(t_lexer *token, t_env *test, t_ex *ex)
{
	if (test && test->value)
	{
		ex->new_word = malloc((ft_strlen(token->doc_data)
					- ex->pk) + ft_strlen(test->value) + 1);
		ex->c_p_dollar = 0;
		while (ex->c_p_dollar < ex->x - 1)
			ex->new_word[ex->y++] = token->doc_data[ex->c_p_dollar++];
		while (test->value[ex->i])
			ex->new_word[ex->y++] = test->value[ex->i++];
		while (token->doc_data[ex->c_p_dollar + ex->pk])
			ex->new_word[ex->y++] = token->doc_data[ex->c_p_dollar + ++ex->pk];
		ex->new_word[ex->y] = 0;
	}
	else
	{
		ex->new_word = malloc((ft_strlen(token->doc_data) - ex->pk) + 1);
		ex->c_p_dollar = 0;
		while (ex->c_p_dollar < ex->x - 1)
			ex->new_word[ex->y++] = token->doc_data[ex->c_p_dollar++];
		while (token->doc_data[ex->c_p_dollar + ex->pk])
			ex->new_word[ex->y++] = token->doc_data[ex->c_p_dollar + ++ex->pk];
		ex->new_word[ex->y] = 0;
	}
	free(token->doc_data);
	free(ex->key);
}

void	search_fordollar(t_ex *ex, t_lexer *token)
{
	while (token->doc_data[ex->x] && token->doc_data[ex->x] != '$')
		ex->x++;
}

void	helper_0(t_lexer *t, t_env *env, t_ex *e)
{
	t_env	*test;

	if ((t->doc_data[e->x + 1] && t->doc_data[e->x + 1] == ' ')
		|| (t->doc_data[e->x + 1] && t->doc_data[e->x + 1] == '\t'))
		e->x++;
	else
	{
		e->c_p_dollar = ((e->pk = 0), ++e->x);
		while ((t->doc_data[e->x + e->pk] && t->doc_data[e->x + e->pk] >= '0'
				&& t->doc_data[e->x + e->pk] <= '9')
			|| (t->doc_data[e->x + e->pk] && t->doc_data[e->x + e->pk] >= 'A'
				&& t->doc_data[e->x + e->pk] <= 'Z')
			|| (t->doc_data[e->x + e->pk] && t->doc_data[e->x + e->pk] >= 'a'
				&& t->doc_data[e->x + e->pk] <= 'z')
			|| (t->doc_data[e->x + e->pk] && t->doc_data[e->x + e->pk] == '_')
			|| (t->doc_data[e->x + e->pk] && t->doc_data[e->x + e->pk] == '?'))
			e->pk++;
		e->key = ft_substr2(t->doc_data, e->c_p_dollar, e->pk + e->x);
		test = get_env_var(env, e->key);
		helper_1(t, test, e);
		t->doc_data = ((e->dollar--), (e->x = e->c_p_dollar), e->new_word);
		e->c_p_dollar = ((e->pk = 0), (e->y = 0), (e->i = 0), 0);
	}
}

void	expand_herdoc(t_lexer *token, t_env *env)
{
	t_ex	*ex;

	ex = (t_ex *)malloc(sizeof(t_ex));
	ex->x = ((ex->y = 0, ex->i = 0, ex->dollar = 0, ex->pk = 0), 0);
	ex->c_p_dollar = 0;
	ex->dollar = how_many_dollar(token->doc_data, '$');
	while (ex->dollar != 0)
	{
		search_fordollar(ex, token);
		helper_0(token, env, ex);
		ex->dollar = how_many_dollar(token->doc_data + ex->x, '$');
	}
	ex->dollar = 0;
	free(ex);
}
