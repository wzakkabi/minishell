/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toor <toor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 19:30:45 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/08/18 00:20:07 by toor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*daba kan7awel ngad "lexer o parser" ela 7essab had struct li endi ila fik li i9lb ela executor
bach tfhm l pipex kifach khdamin nkon ana salit lexer o parser and expander too ila jat blan golha liya
ila jab lah o mabantch lik chi haja wadha fl code golha liya 
had lcode mazal ghir kanchof kifach n parser thing to the correct way */
// hada ghir test ila kant endk chi idea ola chi l3ba golha liya

t_ast *newnode()
{
	t_ast *new;
	new = (t_ast *)malloc(sizeof(t_ast));
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
	//printf("nn = %d\n", i);
	return new;
}
void	check_quest(char *str)
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
				ft_putstr_fd("error double quest", 1);
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
				ft_putstr_fd("error single quest", 1);
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
	lx->word = ft_substr2(ret, y, cnt);
	//printf("word = (%s) (node = %d) y = %d cnt = %d\n", lx->word, lx->num_node , y, cnt);
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
			while(ret[cnt] != qst && ret[cnt])
				cnt++;
			cnt++;
				lx = creat_node_word(lx, ret, y , cnt);
			y = cnt;
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
	ft_print(lx);
	return lx;
	//printf("%s\n", ft_substr2(ret, 6 , 11));
}
void ft_print(t_lexer *lx)
{
	//printf("%d\n", lx->num_node);
	while(lx->prev != NULL)
		lx = lx->prev;
	//printf("1111\n");
	while(lx->next != NULL)
	{
		
		if(lx->word != NULL )
			printf("word = (%s)\n", lx->word);
		else
			printf("token = (%d)\n", lx->token);
		lx = lx->next;
	}
}
void    minishell_loop(t_ast *tool)
{
	char *input;
	t_lexer *token;
	input = readline("minishell~>");
	if(input == NULL || input[0] == 0)
	{
		free(input);
		minishell_loop(tool);
	}
	check_quest(input);	
	token = ft_token(input);
}

int main(int c, char **av)
{
	t_ast *tool;
	tool = newnode();
	if (c > 1 || av[1])
	{
		printf("this program dont take paramiter");
		exit(0);
	}
	minishell_loop(tool);
	return 0;
}