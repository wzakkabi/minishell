/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 19:30:45 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/07/26 00:56:26 by wzakkabi         ###   ########.fr       */
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
void    split_to_ast(t_ast *tool, char *s)
{
	int x = -1;
	int y = 0;
	char *p;
	while(s[++x])
	{
		if(s[x] == 34)
		{
			x++;
			while(s[x] != 34)
				x++;
		}
		else if(s[x] == 39)
		{
			x++;
			while(s[x] != 39)
				x++;
		}
		else if(s[x] == '|')
		{
			tool->cmd = ft_substr(s, y, x - y);
			y = x + 1;
			//tool->cmd = ft_split(p, ' ');
			//free(p);
			tool->next = newnode();
			tool->next->prev = tool;
			tool = tool->next;
		}
		if(s[x + 1] == '\0')
		{
			tool->cmd = ft_substr(s, y, x - y + 1);
			//tool->cmd = ft_split(p, ' ');
			//free(p);
		}
	}
}

void print(t_ast *s)
{
	int x = 0;
	int node=1;
	while(s->prev != NULL)
	{
		printf("1\n");
		s = s->prev;
	}
	while(s != NULL)
	{
		x = 0;
		printf("node == %d (%s)\n",node ,s->cmd);
		s = s->next;
		node++;
	}
}

char *chrandreplace(char *s, int find, int replace)
{
	int x;
	char *p;

	p = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	x = 0;
	while (s[x])
	{
		if (s[x] == find)
			p[x] = replace;
		else
			p[x] = s[x];
		x++;
	}
	free(s);
	return (p);
}
void	check_quest(char *p)
{
	int x = 0;
	while(p[x])
	{
		if(p[x] == 34)
		{
			x++;
			while(p[x] != 34 && p[x])
				x++;
			if(p[x] == 0)
			{
				ft_putstr_fd("error double quest", 1);
				exit(1);
			}
		}
		else if (p[x] == 39)
		{
			x++;
			while(p[x] != 39 && p[x])
				x++;
			if(p[x] == 0)
			{
				ft_putstr_fd("error single quest", 1);
				exit(1);
			}
		}
		x++;
	}
}

void    minishell_loop(t_ast *tool)
{
	char *input;

	input = readline("minishell~>");
	if(input == NULL || input[0] == 0)
	{
		free(input);
		minishell_loop(tool);
	}
	input = chrandreplace(input, '\t', ' ');
	check_quest(input);
	split_to_ast(tool, input);
	print(tool);
	write(1, "\n\n", 2);
	minishell_loop(tool);
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