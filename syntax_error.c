/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:19:33 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/10/20 20:34:49 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *str, t_env *env)
{
	int	x;
	int	y;

	x = ((y = 0), -1);
	while (str[++x])
	{
		if (str[x] == 34)
		{
			x++;
			while (str[x] != 34 && str[x])
				x++;
			if (str[x] == 0)
				ft_putstr_fd("minishell~>: error double quote\n", ++y);
		}
		else if (str[x] == 39 && x++)
		{
			while (str[x] != 39 && str[x])
				x++;
			if (str[x] == 0)
				ft_putstr_fd("minishell~>: error single quote\n", ++y);
		}
	}
	if (y == 1)
		ft_exit(env, 2);
	return (y);
}

int	check_syntax_error(t_env *env, t_lexer *err)
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
				ft_exit(env, 1);
				ft_free_token(err);
				return printf("minishell->: syntax error\n");
			}
			i = 1;
		}
		else
			i = 0;
		err = err->next;
	}
	return 0;
}

int	check_syntax_error_again(t_ast *tool)
{
	t_lexer	*new;

	while (tool)
	{
		new = tool->redirections;
		while (tool->redirections)
		{
			if (tool->redirections->token >= GREAT
				&& tool->redirections->token <= LESS
				&& ft_strlen(tool->redirections->word) == 0)
				return (printf("minishell~>: no such file or directory\n"));
			tool->redirections = tool->redirections->next;
		}
		tool->redirections = new;
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
