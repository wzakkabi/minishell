/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:20:15 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/10/31 03:30:34 by mbousbaa         ###   ########.fr       */
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
	if (test)
	{
		ex->new_word = malloc((ft_strlen(token->doc_data)
					- ex->c_p_key) + ft_strlen(test->value) + 1);
		ex->c_p_dollar = 0;
		while (ex->c_p_dollar < ex->x - 1)
			ex->new_word[ex->y++] = token->doc_data[ex->c_p_dollar++];
		while (test->value[ex->i])
			ex->new_word[ex->y++] = test->value[ex->i++];
		while (token->doc_data[ex->c_p_dollar + ex->c_p_key])
			ex->new_word[ex->y++] = token->doc_data[ex->c_p_dollar + ++ex->c_p_key];
		ex->new_word[ex->y] = 0;
	}
	else
	{
		ex->new_word = malloc((ft_strlen(token->doc_data) - ex->c_p_key) + 1);
		ex->c_p_dollar = 0;
		while (ex->c_p_dollar < ex->x - 1)
			ex->new_word[ex->y++] = token->doc_data[ex->c_p_dollar++];
		while (token->doc_data[ex->c_p_dollar + ex->c_p_key])
			ex->new_word[ex->y++] = token->doc_data[ex->c_p_dollar + ++ex->c_p_key];
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

void	helper_0(t_lexer *token, t_env *env, t_ex *ex)
{
	t_env	*test;

	if (token->doc_data[ex->x + 1] == ' '
		|| token->doc_data[ex->x + 1] == '\t')
	{
		while ((token->doc_data[ex->x + 1] && token->doc_data[ex->x + 1] == ' ')
			|| (token->doc_data[ex->x + 1] && token->doc_data[ex->x + 1] == '\t')
			|| (token->doc_data[ex->x + 1] && token->doc_data[ex->x + 1] == '\n'))
			ex->x++;
	}
	else
	{
		ex->c_p_dollar = ((ex->c_p_key = 0), ++ex->x);
		while (token->doc_data[ex->x + ex->c_p_key]
			&& token->doc_data[ex->x + ex->c_p_key] != '$'
			&& token->doc_data[ex->x + ex->c_p_key] != '\n'
			&& token->doc_data[ex->x + ex->c_p_key] != '\t'
			&& token->doc_data[ex->x + ex->c_p_key] != ' '
			&& token->doc_data[ex->x + ex->c_p_key] != 34
			&& token->doc_data[ex->x + ex->c_p_key] != 39)
			ex->c_p_key++;
		ex->key = ft_substr2(token->doc_data, ex->c_p_dollar, ex->c_p_key + ex->x);
		test = get_env_var(env, ex->key);
		helper_1(token, test, ex);
		token->doc_data = ((ex->dollar--), (ex->x = ex->c_p_dollar), ex->new_word);
		ex->c_p_dollar = ((ex->c_p_key = 0), (ex->y = 0), (ex->i = 0), 0);
	}
}

void	expand_herdoc(t_lexer *token, t_env *env)
{
	t_ex	*ex;

	ex = (t_ex *)malloc(sizeof(t_ex));
	ex->x = ((ex->y = 0, ex->i = 0, ex->dollar = 0, ex->c_p_key = 0), 0);
	ex->c_p_dollar = 0;
	ex->dollar = how_many_dollar(token->doc_data, '$');
	while (ex->dollar != 0)
	{
		ex->x = 0;
		search_fordollar(ex, token);
		helper_0(token, env, ex);
		ex->dollar = how_many_dollar(token->doc_data + ex->x, '$');
	}
	ex->dollar = 0;
	free(ex);
}

void read_heardoc(t_ast *cmds, t_env* env)
{
	t_ast *head;
	t_lexer *head_r;
	pid_t pid;
	int status;
	int pip[2];
	
	head = cmds;
	while(head)
	{
		head_r = head->redirections;
		while(head_r && head_r->token == LESS_LESS)
		{
			if (pipe(pip) == -1)
				return ;
			pid = fork();
			if (pid == -1)
				return ;
			if (pid == 0)
			{
				close(pip[0]);
				while (1)
				{
					head_r->doc_data = readline("heredoc> ");
					if (!head_r->doc_data
						|| ft_memcmp(head_r->doc_data, head_r->word, ft_strlen(head_r->word) + 1) == 0)
						break ;
					if(head_r->q == 0)
						expand_herdoc(head_r, env);
					ft_putstr_fd(head_r->doc_data, pip[1]);
					ft_putchar_fd('\n', pip[1]);
					free(head_r->doc_data);
				}
				close(pip[1]);
				exit(0);
			}
			close(pip[1]);
			waitpid(pid, &status, 0);
			head_r->fd = pip;
			head_r = head_r->next;
		}
		head = head->next;
	}
}
