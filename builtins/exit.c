/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:21:07 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/10/17 00:36:43 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	putstr_exit(char *str, int fd, int exit_state)
{
	ft_putstr_fd(str, fd);
	exit(exit_state);
}

void	builtin_exit(t_ast *ast)
{
	int	i;

	i = -1;
	while (ast->str[++i]);
	if (i > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return ;
	}
	else if (i == 1)
		putstr_exit("exit\n", STDOUT_FILENO, 0);
	i = -1;
	while (ast->str[1][++i])
		if (!ft_isdigit(ast->str[1][i])
			&& (ast->str[1][i] != '-' && ast->str[1][i] != '+'))
			break ;
	if (i != (int) ft_strlen(ast->str[1]))
		putstr_exit("exit\nminishell: exit: numeric argument required\n",
			STDERR_FILENO, 2);
	else
		putstr_exit("exit\n", STDOUT_FILENO, ft_atoi(ast->str[1]));	
}