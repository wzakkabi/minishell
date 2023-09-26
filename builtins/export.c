/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 03:05:47 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/09/26 04:14:31 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**parse_param(char *str)
{
	char	**ret;
	int		i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (NULL);
	i = 1;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
		{
			printf("illegal caracter : %c\n", str[i]);
			return (NULL);
		}
		i++;
	}
	ret = ft_split(str, '=');
	return (ret);
}

int export(t_ast *ast, t_env *env)
{
	int		i;
	t_env	*env_p;
	char	**key_val_env;

	i = 0;
	while (ast->str[i])
		i++;
	if (i == 1)
	{
		env_p = env;
		while (env_p)
		{
			ft_putstr_fd(env_p->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			if (env_p->value)
				ft_putstr_fd(env_p->value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			env_p = env_p->next;
		}
		return (0);
	}
	else
	{
		i = 0;
		while (ast->str[++i])
		{
			key_val_env = parse_param(ast->str[i]);
			if (!key_val_env)
				printf("export: naming variable error \n");
			if(!add_env_var(&env, key_val_env[0], key_val_env[1]))
				printf("export: error adding env var\n");
		}
	}
	return (0);
}