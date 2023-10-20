/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:35:12 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/10/20 18:15:23 by wzakkabi         ###   ########.fr       */
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
	int		c_p_key;
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
		if (s[x] == c)
			find++;
	}
	return (find);
}

void	expand_helper_1(t_lexer *token, t_env *test, t_ex *ex)
{
	if (test)
	{
		ex->new_word = malloc((ft_strlen(token->word)
					- ex->c_p_key) + ft_strlen(test->value));
		ex->c_p_dollar = 0;
		while (ex->c_p_dollar < ex->x - 1)
			ex->new_word[ex->y++] = token->word[ex->c_p_dollar++];
		while (test->value[ex->i])
			ex->new_word[ex->y++] = test->value[ex->i++];
		while (token->word[ex->c_p_dollar + ex->c_p_key])
			ex->new_word[ex->y++] = token->word[ex->c_p_dollar + ++ex->c_p_key];
		ex->new_word[ex->y] = 0;
	}
	else
	{
		ex->new_word = malloc((ft_strlen(token->word) - ex->c_p_key));
		ex->c_p_dollar = 0;
		while (ex->c_p_dollar < ex->x - 1)
			ex->new_word[ex->y++] = token->word[ex->c_p_dollar++];
		while (token->word[ex->c_p_dollar + ex->c_p_key])
			ex->new_word[ex->y++] = token->word[ex->c_p_dollar + ++ex->c_p_key];
		ex->new_word[ex->y] = 0;
	}
	free(token->word);
	free(ex->key);
}

void	expand_helper_0(t_lexer *token, t_env *env, t_ex *ex)
{
	t_env	*test;

	while (token->word[ex->x] != '$')
		ex->x++;
	if (token->word[ex->x + 1] == ' '
		|| token->word[ex->x + 1] == '\t'
		|| token->word[ex->x + 1] == 0
		|| token->word[ex->x + 1] == 34)
		ex->x++;
	else
	{
		ex->c_p_dollar = ((ex->c_p_key = 0), ++ex->x);
		while (token->word[ex->x + ex->c_p_key] != ' '
			&& token->word[ex->x + ex->c_p_key] != '$'
			&& token->word[ex->x + ex->c_p_key] != '\t'
			&& token->word[ex->x + ex->c_p_key]
			&& token->word[ex->x + ex->c_p_key] != 34
			&& token->word[ex->x + ex->c_p_key] != 39)
			ex->c_p_key++;
		ex->key = ft_substr2(token->word, ex->c_p_dollar, ex->c_p_key + ex->x);
		test = get_env_var(env, ex->key);
		expand_helper_1(token, test, ex);
		token->word = ((ex->dollar--), ex->new_word);
		ex->c_p_dollar = ((ex->c_p_key = 0), (ex->y = 0), (ex->i = 0), 0);
	}
}

void	check_expand(t_lexer *token, t_env *env)
{
	t_ex	ex;

	ex.x = ((ex.y = 0, ex.i = 0, ex.dollar = 0, ex.c_p_key = 0), 0);
	ex.c_p_dollar = 0;
	while (token->next)
	{
		if (token->token == LESS_LESS)
			token = ((token = token->next), token->next);
		else
		{
			ex.dollar = how_many(token->word, '$');
			while (ex.dollar != 0)
			{
				expand_helper_0(token, env, &ex);
				ex.dollar = how_many(token->word + ex.x, '$');
			}
			token = token->next;
			ex.dollar = 0;
		}
	}
}
