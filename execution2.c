/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 04:54:32 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/10/21 08:08:41 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./builtins/builtins.h"

void	put_strerror(t_ast *ast, int __errno)
{
	ft_putstr_fd(ast->str[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(__errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

char	**get_bin_paths(t_env *env)
{
	int		i;
	char	**ret;
	char	*tmp;
	t_env	*env_p;

	if (!env)
		return (NULL);
	env_p = get_env_var(env, "PATH");
	if (!env_p)
		return (NULL);
	ret = ft_split(env_p->value, ':');
	i = -1;
	while (ret[++i])
	{
		if (ret[i][ft_strlen(ret[i]) - 1] != '/')
		{
			tmp = ft_strjoin(ret[i], "/");
			free(ret[i]);
			ret[i] = ft_strdup(tmp);
			free(tmp);
		}
	}
	return (ret);
}

char	**get_envp(t_env *env)
{
	t_env	*env_p;
	char	**ret;
	char	*tmp;
	int		i;

	i = ((env_p = env), 0);
	while (env_p)
	{
		if (env_p->value)
			i++;
		env_p = env_p->next;
	}
	i = ((ret = malloc(sizeof(char *) * (i + 1))), -1);
	while (env)
	{
		if (env->value)
		{
			tmp = ft_strjoin(env->key, "=");
			ret[++i] = ft_strjoin(tmp, env->value);
			free(tmp);
		}
		env = env->next;
	}
	ret[i] = NULL;
	return (ret);
}
