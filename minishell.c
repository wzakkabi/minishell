/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 19:30:45 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/07/16 23:50:14 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **split(char *s)
{
	char **p;
	int x;
	int word;
	int y;

	x = 0;
	word = 0;
	while(s[x])
	{
		while(s[x] == ' ' || s[x] == '\t')
			x++;
		if(s[x])
			word++;
		while(s[x] != ' ' && s[x] != '\t' && s[x])
			x++;
	}
	p = (char **)malloc((word + 1) * sizeof(char *));
	p[word] = 0;
	x = 0;
	y = 0;
	word = 0;
	while(s[x])
	{
		while(s[x] == ' ' || s[x] == '\t')
			x++;
		while(s[x + y] != ' ' && s[x + y] != '\t' && s[x + y])
			y++;
		if(y > 0)
		{
			p[word] = malloc(y + 1 * sizeof(char));
			y = 0;
			while(s[x] != ' ' && s[x] != '\t' && s[x])
				p[word][y++] = s[x++];
			p[word][y] = 0;
			y = 0;
			word++;
		}
	}
	return p;
}


int main() 
{
	char *input;
	char **p;
	int x = 0;
	while(1)
	{
		input = readline("minishell~>");
		add_history(input);
		
		free(input);
	}
	return 0;
}