/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 21:56:12 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/11/03 22:30:03 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_env(t_env *env)
{
	t_env	*env_p;

	env_p = env;
	while (env_p)
	{
		if (env_p->value != NULL && env_p->print_or_not)
		{
			ft_putstr_fd(env_p->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(env_p->value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		env_p = env_p->next;
	}
	return (0);
}
