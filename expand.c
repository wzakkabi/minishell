/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:35:12 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/11/03 17:11:34 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins/builtins.h"

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

int	how_many(char *s, int c)
{
	int	x;
	int	find;
	int	dbl;

	x = ((find = 0), (dbl = 0), -1);
	while (s && s[++x])
	{
		if (s[x] == 39 && dbl == 0)
		{
			x++;
			while (s[x] && s[x] != 39)
				x++;
		}
		if (s[x] == 34)
		{
			if (dbl == 0)
				dbl = 1;
			else
				dbl = 0;
		}
		if (s[x] == c && s[x + 1] != 0)
			find++;
	}
	return (find);
}

void	expand_helper_1(t_lexer *token, t_env *test, t_ex *ex)
{
	if (test)
	{
		ex->new_word = malloc((ft_strlen(token->word)
					- ex->pk) + ft_strlen(test->value) + 1);
		ex->c_p_dollar = 0;
		while (ex->c_p_dollar < ex->x - 1)
			ex->new_word[ex->y++] = token->word[ex->c_p_dollar++];
		while (test->value[ex->i])
			ex->new_word[ex->y++] = test->value[ex->i++];
		while (token->word[ex->c_p_dollar + ex->pk])
			ex->new_word[ex->y++] = token->word[ex->c_p_dollar + ++ex->pk];
		ex->new_word[ex->y] = 0;
	}
	else
	{
		ex->new_word = malloc((ft_strlen(token->word) - ex->pk) + 1);
		ex->c_p_dollar = 0;
		while (ex->c_p_dollar < ex->x - 1)
			ex->new_word[ex->y++] = token->word[ex->c_p_dollar++];
		while (token->word[ex->c_p_dollar + ex->pk])
			ex->new_word[ex->y++] = token->word[ex->c_p_dollar + ++ex->pk];
		ex->new_word[ex->y] = 0;
	}
	free(token->word);
	free(ex->key);
}

void	search_for_dollar(t_ex *ex, t_lexer *token)
{
	while (token->word[ex->x] && token->word[ex->x] != '$')
	{
		if (token->word[ex->x] == 34)
		{
			while (token->word[++ex->x] != 34)
			{
				if (token->word[ex->x] == '$')
					return ;
			}
		}
		else if (token->word[ex->x] == 39)
		{
			while (token->word[++ex->x] != 39)
				ex->x += 0;
		}
		ex->x++;
	}
}

void	expand_helper_0(t_lexer *tk, t_env *env, t_ex *ex)
{
	t_env	*test;

	if ((tk->word[ex->x + 1] && tk->word[ex->x + 1] == ' ')
		|| (tk->word[ex->x + 1] && tk->word[ex->x + 1] == '\t'))
		ex->x++;
	else
	{
		ex->c_p_dollar = ((ex->pk = 0), ++ex->x);
		while ((tk->word[ex->x + ex->pk] && tk->word[ex->x + ex->pk] >= '0'
				&& tk->word[ex->x + ex->pk] <= '9')
			|| (tk->word[ex->x + ex->pk] && tk->word[ex->x + ex->pk] >= 'A'
				&& tk->word[ex->x + ex->pk] <= 'Z')
			|| (tk->word[ex->x + ex->pk] && tk->word[ex->x + ex->pk] >= 'a'
				&& tk->word[ex->x + ex->pk] <= 'z')
			|| (tk->word[ex->x + ex->pk] && tk->word[ex->x + ex->pk] == '_')
			|| (tk->word[ex->x + ex->pk] && tk->word[ex->x + ex->pk] == '?'))
			ex->pk++;
		ex->key = ft_substr2(tk->word, ex->c_p_dollar, ex->pk + ex->x);
		test = get_env_var(env, ex->key);
		expand_helper_1(tk, test, ex);
		tk->word = ((ex->dollar--), (ex->x = ex->c_p_dollar), ex->new_word);
		ex->c_p_dollar = ((ex->pk = 0), (ex->y = 0), (ex->i = 0), 0);
	}
}

void	check_expand(t_lexer *token, t_env *env)
{
	t_ex	*ex;

	ex = (t_ex *)malloc(sizeof(t_ex));
	ex->x = ((ex->y = 0, ex->i = 0, ex->dollar = 0, ex->pk = 0), 0);
	ex->c_p_dollar = 0;
	while (token && token->next)
	{
		if (token->token == LESS_LESS)
			token = ((token = token->next), token->next);
		else
		{
			ex->dollar = how_many(token->word, '$');
			while (ex->dollar != 0)
			{
				search_for_dollar(ex, token);
				expand_helper_0(token, env, ex);
				ex->dollar = how_many(token->word + ex->x, '$');
			}
			token = token->next;
			ex->dollar = 0;
		}
	}
	free(ex);
}
