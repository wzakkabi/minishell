/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:20:40 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/10/17 00:28:23 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	pwd(t_ast *ast)
{
	char	path[PATH_MAX];
	int		i;

	if (!ast)
		return (0);
	if (!ast->builtins || ft_strncmp(ast->str[0], "pwd", 3)
		|| ft_strlen(ast->str[0]) != 3)
		return (0);
	i = 0;
	while (ast->str[i])
		i++;
	if (i > 1)
	{
		ft_putstr_fd("pwd: too many arguments\n", STDERR_FILENO);
		return (0);
	}
	if (!getcwd(path, sizeof(path)))
	{
		perror("getcwd()");
		return (0);
	}
	ft_putstr_fd(path, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (1);
}
