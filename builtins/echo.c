/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 04:24:39 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/11/01 14:50:26 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	parse_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		while (str[++i])
			if (str[i] != 'n')
				return (0);
		return (1);
	}
	return (0);
}

void	echo(t_ast *ast)
{
	int	i;
	int	is_option;

	i = 0;
	is_option = 0;
	while (ast->str[i])
		i++;
	if (i > 1)
	{
		i = 1;
		is_option = parse_option(ast->str[i]);
		if (!is_option)
			i = 0;
		while (ast->str[++i])
		{
			ft_putstr_fd(ast->str[i], STDOUT_FILENO);
			if (ast->str[i + 1] != NULL)
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
	}
	if (!is_option)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
