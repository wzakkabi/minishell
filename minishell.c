/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 19:30:45 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/09/24 21:06:50 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins/builtins.h"


/*daba kan7awel ngad "lexer o parser" ela 7essab had struct li endi ila fik li i9lb ela executor
bach tfhm l pipex kifach khdamin nkon ana salit lexer o parser and expander too ila jat blan golha liya
ila jab lah o mabantch lik chi haja wadha fl code golha liya 
had lcode mazal ghir kanchof kifach n parser thing to the correct way */
// hada ghir test ila kant endk chi idea ola chi l3ba golha liya

t_ast *newnode()
{
	t_ast *new;
	new = (t_ast *)malloc(sizeof(t_ast));
	new->str = (char **)calloc(sizeof(char *) , 10);
	new->num_redirections = 0;
	new->next = NULL;
	new->prev = NULL;
	return new;
}

t_lexer *lxnewnode()
{
	t_lexer *new;
	static int i = 0;
	new = (t_lexer *)malloc(sizeof(t_lexer));
	new->num_node = i;
	new->next = NULL;
	new->prev = NULL;
	i++;
	return new;
}
t_env *envnode()
{
	t_env *new;
	new = (t_env *)malloc(sizeof(t_env));
	new->next = NULL;
	new->prev = NULL;
}
void	check_quote(char *str)
{
	int x = 0;
	while(str[x])
	{
		if(str[x] == 34)
		{
			x++;
			while(str[x] != 34 && str[x])
				x++;
			if(str[x] == 0)
			{
				ft_putstr_fd("error double quote", 1);
				exit(1);
			}
		}
		else if (str[x] == 39)
		{
			x++;
			while(str[x] != 39 && str[x])
				x++;
			if(str[x] == 0)
			{
				ft_putstr_fd("error single quote", 1);
				exit(1);
			}
		}
		x++;
	}
}

int token_or_not(char c, char c1)
{
	if (c == '<' && c1 == '<')
		return 0;
	else if (c == '>' && c1 == '>')
		return 1;
	else if (c == '<')
		return 2;
	else if (c == '>')
		return 3;
	else if(c == '|')
		return 4;
	return 6;
}

t_lexer *creat_node_token(char c, char c1, t_lexer *lx)
{
	t_token test;
	if (c == '<' && c1 == '<')
		test =  LESS_LESS;
	else if (c == '>' && c1 == '>')
		test =  GREAT_GREAT;
	else if (c == '<')
		test =  LESS;
	else if (c == '>')
		test =  GREAT;
	else if(c == '|')
		test =  PIPE;
	lx->token = test;
	lx->word = NULL;
	lx->next = lxnewnode();
	lx->next->prev = lx;
	return lx->next;
}

t_lexer	*creat_node_word(t_lexer *lx, char *ret, int y , int cnt)
{
	if(y == cnt)
		return lx;
	lx->token = -1;
	lx->word = ft_substr2(ret, y, cnt);
	lx->next = lxnewnode();
	lx->next->prev = lx;
	return lx->next;
}

t_lexer	*ft_token(char *ret)
{
	int cnt = 0;
	t_lexer *lx;
	char *p;
	int y = 0;
	int test;
	int qst;
	lx = lxnewnode();
	while (ret[cnt])
	{
		test = token_or_not(ret[cnt], ret[cnt + 1]);
		if(ret[cnt] == 34 || ret[cnt] == 39)
		{
			qst = ret[cnt];
			cnt++;
			test = cnt;
			while(ret[cnt] != qst && ret[cnt])
				cnt++;
			if(test != cnt)
			{
				cnt++;
					lx = creat_node_word(lx, ret, y , cnt);
				y = cnt;
			}
			else
				y =	++cnt;
		}
		else if(test == 0 || test == 1 || test == 2 || test == 3 || test == 4)
		{
			lx = creat_node_token(ret[cnt], ret[cnt + 1], lx);
			if(test == 0 || test == 1)
				cnt += 2;
			else
				cnt++;
			y = cnt;
		}
		else if(ret[cnt] == ' ' || ret[cnt] == '\t')
		{
			lx = creat_node_word(lx, ret, y, cnt);
			cnt++;
			y = cnt;
		}
		else
		{
			cnt++;
			if((ret[cnt] == 0 && ret[cnt - 1] != ' ') && (ret[cnt] == 0 && ret[cnt - 1] != '\t'))
			{
				lx = creat_node_word(lx, ret, y, cnt);
			}
		}
	}
	return lx;
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
			printf("ast == (%s)\n", lx->str[x]);
			x++;
		}
		while(lx->redirections)
		{
			printf("word = (%s) and token = (%d)\n", lx->redirections->word, lx->redirections->token);
			lx->redirections = lx->redirections->next;
		}
		x = 0;
		lx = lx->next;
	}
}

t_ast *split_to_ast(t_lexer *lx)
{
	t_ast *tool;
	int cnt = 0;
	tool = newnode();
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
			//printf("token == %d\n", lx->token);
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
			tool->num_redirections += 1;
			//printf("toekn (%d) and word (%s)\n", tool->redirections->token, tool->redirections->word);
		}
		else if(lx->word != NULL)
		{ 
			tool->str[cnt] = lx->word;
			//printf("str = %s\n",tool->str[cnt]);
			cnt++;
		}
		lx = lx->next;
	}
	return tool;
}

void	check_syntax_error(t_lexer *err)
{
	int i = 0;
	while(err->prev)
		err = err->prev;
	while(err)
	{
		if(err->token >= GREAT && err->token <= PIPE)
		{
			if(i == 1)
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

void	check_expand(t_lexer *token, t_env *env)
{
	int x = 0, y = 0, i = 0;
	int c_p_dollar = 0, c_p_key = 0;
	char *key;
	char *new_word;
	t_env *test;

	while(token->next != NULL)
	{
		if(ft_strrchr(token->word, '$') != NULL && token->word[0] != 39 && token->word)
		{
			while(token->word[x] != '$')
				x++;
			c_p_dollar = ++x;
			c_p_key = 0;
			while(token->word[x + c_p_key] != ' ' && token->word[x + c_p_key] != '$' && token->word[x + c_p_key] != '\t' && token->word[x + c_p_key] && token->word[x + c_p_key] != 34)
				c_p_key++;
			key = ft_substr2(token->word, c_p_dollar, c_p_key + x);
			test = get_env_var(env, key);
			if(test)
			{
				new_word = malloc((ft_strlen(token->word) - c_p_key) + ft_strlen(test->value));
				x = 0;
				while(token->word[x] != '$' && token->word)
					new_word[y++] = token->word[x++];
				while(test->value[i])
					new_word[y++] = test->value[i++];
				while(token->word[x + c_p_key])
					new_word[y++] = token->word[x + ++c_p_key];
				new_word[y] = 0;
			}
			else
			{
				new_word = malloc((ft_strlen(token->word) - c_p_key));
				x = 0;
				while(token->word[x] != '$' && token->word)
					new_word[y++] = token->word[x++];
				while(token->word[x + c_p_key])
					new_word[y++] = token->word[x + ++c_p_key];
				new_word[y] = 0;
			}
			free(token->word);
			free(key);
			token->word = new_word;

		}
		else
		{
			token = token->next;
		}
		c_p_dollar = 0;
		c_p_key = 0;
		y = 0;
		x = 0;
		i = 0;
	}
}

void	remove_qost(t_lexer *token)
{
	char *new_word;
	int x = 0, y = 0;
	while (token->next)
	{
		if(token->word)
		{
			if(token->word[0] == 34 || token->word[0] == 39) 
			{
				new_word = malloc(ft_strlen(token->word) - 2);
				while(token->word[++x] != token->word[0])
					new_word[y++] = token->word[x];
				new_word[y] = 0;
				free(token->word);
				token->word = new_word;
			}
		}
		token = token->next;
	}
	
}
//&& token->word

void    minishell_loop(t_ast *tool, t_lexer *token, t_env *env)
{
	char *input;
	
	input = readline("minishell~>");
	if(input == NULL || input[0] == 0)
	{
		free(input);
		minishell_loop(tool, token, env);
	}
	check_quote(input);
	token = ft_token(input);
	while(token->prev != NULL)
		token = token->prev;
	check_syntax_error(token);
	check_expand(token, env);
	remove_qost(token);
	tool = split_to_ast(token);
	 ft_printast(tool);
	// while(tool->prev != NULL)
		// tool = tool->prev;
	execute(tool, env);
}

void *make_env_node(char **env, t_env *node)
{
	int cnt_x = 0;
	int cnt_y = 0;
 	while(env[cnt_y])
	{
		while(env[cnt_y][cnt_x] != '=' && env[cnt_y][cnt_x])
			cnt_x++;
		node->key = ft_substr2(env[cnt_y], 0, cnt_x);
		node->value = ft_substr2(env[cnt_y] , cnt_x + 1, ft_strlen(env[cnt_y]));
		// printf("node->key == (%s)", node->key);
		// printf("node->value == (%s)\n", node->value);
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