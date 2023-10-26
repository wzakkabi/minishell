/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:06:51 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/10/17 00:32:00 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static	int	parse_param(char *str)
{
	int		i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 0;
	while (str[++i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
		{
			ft_putstr_fd("illegal caracter : ", STDERR_FILENO);
			ft_putchar_fd(str[i], STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
			return (0);
		}
	}
	return (1);
}

int	unset(t_ast *ast, t_env *env)
{
	int		i;

	i = 0;
	while (ast->str[i])
		i++;
	if (i == 1)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		return (0);
	}
	else
	{
		i = 0;
		while (ast->str[++i])
		{
			if (parse_param(ast->str[i]))
				unset_env_var(&env, ast->str[i]);
		}
	}
	return (0);
}