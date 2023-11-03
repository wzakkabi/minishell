/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 04:24:39 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/11/03 20:57:12 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	parse_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		if (str[i + 1] == '\0')
			return (0);
		while (str[++i])
		{
			if (str[i] != 'n')
				return (0);
		}
		return (1);
	}
	return (0);
}

int	check_args(char	**cmd, int *is_option)
{
	int	ret;
	int	i;

	i = 1;
	*is_option = parse_option(cmd[i]);
	if (!(*is_option))
		return (i);
	while (cmd[++i])
	{
		ret = parse_option(cmd[i]);
		if (ret == 0)
			return (i);
	}
	return (i);
}

int	echo(t_ast *ast)
{
	int	i;
	int	is_option;

	i = 0;
	is_option = 0;
	while (ast->str[i])
		i++;
	if (i > 1)
	{
		i = check_args(ast->str, &is_option);
		while (ast->str[i])
		{
			ft_putstr_fd(ast->str[i], STDOUT_FILENO);
			if (ast->str[i + 1] != NULL)
				ft_putchar_fd(' ', STDOUT_FILENO);
			i++;
		}
	}
	if (!is_option)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
