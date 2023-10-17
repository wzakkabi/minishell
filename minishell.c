/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 19:30:45 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/10/17 01:51:17 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins/builtins.h"

t_ast	*newnode(void)
{
	t_ast	*new;

	new = (t_ast *)malloc(sizeof(t_ast));
	new->str = (char **)calloc(sizeof(char *), 10);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_lexer	*lxnewnode(void)
{
	t_lexer		*new;
	static int	i;

	i = 0;
	new = (t_lexer *)malloc(sizeof(t_lexer));
	new->num_node = i;
	new->next = NULL;
	new->prev = NULL;
	i++;
	return (new);
}

t_env	*envnode(void)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->next = NULL;
	new->prev = NULL;
	return (new);
}


int	check_quote(char *str)
{
	int	x;
	int	y;

	x = ((y = 0), 0);
	while (str[x])
	{
		if (str[x] == 34)
		{
			x++;
			while (str[x] != 34 && str[x])
				x++;
			if (str[x] == 0)
				ft_putstr_fd("error double quote\n", ++y);
		}
		else if (str[x] == 39)
		{
			x++;
			while (str[x] != 39 && str[x])
				x++;
			if (str[x] == 0)
				ft_putstr_fd("error single quote\n", ++y);
		}
		x++;
	}
	return (y);
}

void ft_print(t_lexer *lx)
{
	while(lx->prev != NULL)
		lx = lx->prev;
	while(lx->next != NULL)
	{
		
		if(lx->word != NULL )
			printf("word = (%s) %d\n", lx->word, lx->num_node);
		else
			printf("token = (%d) %d\n", lx->token, lx->num_node);
		lx = lx->next;
	}
}

void ft_printast(t_ast *lx)
{
	int x = 0;
	while(lx->prev != NULL)
		lx = lx->prev;
	while(lx != NULL)
	{
		while(lx->str[x])
		{
			printf("ast word == (%s)\n", lx->str[x]);
			x++;
		}
		while(lx->redirections && lx->redirections->prev)
			lx->redirections = lx->redirections->prev;
		while(lx->redirections)
		{
			printf("word = (%s) and token = (%d)\n", lx->redirections->word, lx->redirections->token);
			lx->redirections = lx->redirections->next;
		}
		printf("%d\n", lx->builtins);
		x = 0;
		lx = lx->next;
	}
}

t_ast *split_to_ast(t_lexer *lx)
{
	t_ast *tool_head;
	t_ast *tool;
	int cnt = 0;
	tool = newnode();
	tool_head = tool;
	tool->redirections = NULL;
	while(lx->next != NULL)
	{
		if(lx->token == PIPE)
		{
			tool->next = newnode();
			tool->next->prev = tool;
			tool = tool->next;
			cnt = 0;
			tool->redirections = NULL;
		}
		else if(lx->token == GREAT || lx->token == GREAT_GREAT || lx->token == LESS || lx->token == LESS_LESS)
		{
			if(tool->redirections == NULL)
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
		else if(lx->word != NULL)
		{ 
			tool->str[cnt] = lx->word;
			cnt++;
		}
		lx = lx->next;
	}
	return tool_head;
}

void	check_syntax_error(t_lexer *err)
{
	int	i;

	i = 0;
	while (err->prev)
		err = err->prev;
	while (err)
	{
		if (err->token >= GREAT && err->token <= PIPE)
		{
			if (i == 1)
			{
				printf("syntax error");
				exit(1);
			}
			i = 1;
		}
		else
			i = 0;
		err = err->next;
	}
}

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



void	check_expand(t_lexer *token, t_env *env)
{
	t_ex ex;
	t_env	*test;
	
	ex.x = ((ex.y = 0, ex.i = 0, ex.dollar = 0, ex.c_p_dollar = 0, ex.c_p_key = 0), 0);
	while(token->next)
	{
		if(token->token == LESS_LESS)
		{
			token = token->next;
			token = token->next;
		}
		else
		{
			ex.dollar = how_many(token->word, '$');
			while(ex.dollar != 0)
			{
				while(token->word[ex.x] != '$')
					ex.x++;
				if(token->word[ex.x + 1] == ' ' || token->word[ex.x + 1] == '\t' || token->word[ex.x + 1] == '\0' || token->word[ex.x + 1] == 34)
					ex.x++;
				else
				{
					ex.c_p_dollar = ++ex.x;
					ex.c_p_key = 0;
					while(token->word[ex.x + ex.c_p_key] != ' ' && token->word[ex.x + ex.c_p_key] != '$' && token->word[ex.x + ex.c_p_key] != '\t' && token->word[ex.x + ex.c_p_key] && token->word[ex.x + ex.c_p_key] != 34 && token->word[ex.x + ex.c_p_key] != 39)
						ex.c_p_key++;
					ex.key = ft_substr2(token->word, ex.c_p_dollar, ex.c_p_key + ex.x);
					test = get_env_var(env, ex.key);
					if(test)
					{
						ex.new_word = malloc((ft_strlen(token->word) - ex.c_p_key) + ft_strlen(test->value));
						ex.c_p_dollar = 0;
						while(ex.c_p_dollar < ex.x - 1)
							ex.new_word[ex.y++] = token->word[ex.c_p_dollar++];					
						while(test->value[ex.i])
							ex.new_word[ex.y++] = test->value[ex.i++];
						while(token->word[ex.c_p_dollar + ex.c_p_key])
							ex.new_word[ex.y++] = token->word[ex.c_p_dollar + ++ex.c_p_key];
						ex.new_word[ex.y] = 0;
					}
					else
					{
						ex.new_word = malloc((ft_strlen(token->word) - ex.c_p_key));
						ex.c_p_dollar = 0;
						while(ex.c_p_dollar < ex.x - 1)
							ex.new_word[ex.y++] = token->word[ex.c_p_dollar++];
						while(token->word[ex.c_p_dollar + ex.c_p_key])
							ex.new_word[ex.y++] = token->word[ex.c_p_dollar + ++ex.c_p_key];
						ex.new_word[ex.y] = 0;
					}
					free(token->word);
					free(ex.key);
					token->word = ex.new_word;
					ex.dollar--;
					ex.c_p_dollar = 0;
					ex.c_p_key = 0;
					ex.y = 0;
					ex.i = 0;
				}
				ex.dollar = how_many(token->word + ex.x, '$');
			}
			token = token->next;
			ex.dollar = 0;
		}
	}
}

// t_lexer	*remove_emty_node(t_lexer *token)
// {
// 	t_lexer	*test;

// 	while (token->next)
// 	{
// 		if (token->token == -1 && ft_strlen(token->word) == 0)
// 		{
// 			test = token;
// 			if (token->prev)
// 			{
// 				token->prev->next = token->next;
// 				token->next->prev = token->prev;
// 			}
// 			else
// 			{
// 				token = token->next;
// 				token->prev = NULL;
// 			}
// 			free(test->word);
// 			free(test);
// 		}
// 		token = token->next;
// 	}
// 	while (token->prev)
// 		token = token->prev;
// 	return (token);
// }



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

int	check_syntax_error_again(t_ast *tool)
{
	while (tool)
	{
		while (tool->redirections)
		{
			if (tool->redirections->token >= GREAT
				&& tool->redirections->token <= LESS
				&& ft_strlen(tool->redirections->word) == 0)
				return (printf("minishell~>: no such file or directory\n"));
			tool->redirections = tool->redirections->next;
		}
		if (ft_strncmp(tool->str[0], "cd", 2) == 0
			|| ft_strncmp(tool->str[0], "pwd", 3) == 0
			|| ft_strncmp(tool->str[0], "exit", 4) == 0
			|| ft_strncmp(tool->str[0], "env", 3) == 0
			|| ft_strncmp(tool->str[0], "export", 6) == 0
			|| ft_strncmp(tool->str[0], "unset", 5) == 0
			|| ft_strncmp(tool->str[0], "echo", 4) == 0)
			tool->builtins = 1;
		else
			tool->builtins = 0;
		tool = tool->next;
	}
	return (0);
}


void    minishell_loop(t_ast *tool, t_lexer *token, t_env *env)
{
	char *input;
	
	input = readline("minishell~>");
	if(input == NULL || input[0] == 0 || check_quote(input) == 1)
	{
		free(input);
		minishell_loop(tool, token, env);
	}
	token = ft_token(input);
	while(token->prev != NULL)
		token = token->prev;
	check_syntax_error(token);
	check_expand(token, env);
	remove_qost(token, 0, 0, 0);
	//ft_print(token);
	//token = remove_emty_node(token);
	tool = split_to_ast(token);
	if(check_syntax_error_again(tool) != 0)
		minishell_loop(tool, token, env);
	ft_printast(tool);
	//execute(tool, env);
}

void	make_env_node(char **env, t_env *node)
{
	int	cnt_x;
	int	cnt_y;

	cnt_x = 0;
	cnt_y = 0;
	while (env[cnt_y])
	{
		while (env[cnt_y][cnt_x] != '=' && env[cnt_y][cnt_x])
			cnt_x++;
		node->key = ft_substr2(env[cnt_y], 0, cnt_x);
		node->value = ft_substr2(env[cnt_y], cnt_x + 1, ft_strlen(env[cnt_y]));
		cnt_x = 0;
		cnt_y++;
		node->next = envnode();
		node->next->prev = node;
		node = node->next;
	}
}

int main(int c, char **av, char **grep_env)
{
	t_ast *tool;
	t_lexer *token;
	t_env *env;
	
	
	if (c > 1 || av[1])
	{
		printf("this program dont take paramiter");
		exit(0);
	}
	env = envnode();
	make_env_node(grep_env, env);
	// while(env->next)
	// {
	// 	printf("node->key == (%s)", env->key);
	// 	printf("node->value == (%s)\n", env->value);
	// 	env = env->next;
	// }
	//exit(0);
	minishell_loop(tool, token, env);
	return 0;
}