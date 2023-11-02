/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 03:05:47 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/11/02 22:53:47 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	error__(char *token)
{
	if (!token)
		return ;
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

void	print_env_vars(t_env *env)
{
	t_env	*env_p;

	env_p = env;
	while (env_p)
	{
		if (env_p->key && env_p->print_or_not)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(env_p->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			if (!env_p->value)
				ft_putstr_fd("''", STDOUT_FILENO);
			else
			{
				ft_putchar_fd('"', STDOUT_FILENO);
				ft_putstr_fd(env_p->value, STDOUT_FILENO);
				ft_putchar_fd('"', STDOUT_FILENO);
			}
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		env_p = env_p->next;
	}
}

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
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (NULL);
		i++;
	}
	ret = ft_split(str, '=');
	return (ret);
}

void	update_env_vars(t_env *env, char *key, char *val)
{
	t_env	*current;

	current = get_env_var(env, key);
	if (!current)
		add_env_var(&env, key, val);
	else if (val && ft_strncmp(current->value, val, ft_strlen(val) + 1) != 0)
		update_env_var(env, current->key, val);
}

int	export(t_ast *ast, t_env *env)
{
	int		i;
	char	**key_val_env;

	i = 0;
	while (ast->str[i])
		i++;
	if (i == 1)
		print_env_vars(env);
	else
	{
		i = 0;
		while (ast->str[++i])
		{
			key_val_env = parse_param(ast->str[i]);
			if (key_val_env != NULL)
			{
				update_env_vars(env, key_val_env[0], key_val_env[1]);
				(free(key_val_env[0]), free(key_val_env[1]), free(key_val_env));
			}
			else
				error__(ast->str[i]);
		}
	}
	return (0);
}
