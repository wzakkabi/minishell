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

t_ast	*newnode()
{
	t_ast *newnode;
	
	newnode = (t_ast *)malloc(sizeof(t_ast));
	newnode->next = NULL;
	return newnode;
}

void	build_ast(char *s, t_ast *fill)
{
	int x = 0;
	int y = 0;
	fill = (t_ast *)malloc(sizeof(t_ast));
	char *p;
	while(s[x])
	{
		if(s[x] == '|')
		{
			p = ft_substr(s, y , x - 1);
			fill->p = ft_split(p, ' ');
			y = x + 1;
			fill->next = newnode();
			fill = fill->next;
		}
		x++;
	}
}

int main() 
{
	char *input;
	t_ast start;
	while(1)
	{
		input = readline("minishell~>");
		add_history(input);
		build_ast(input , &start);
		free(input);
	}
	return 0;
}