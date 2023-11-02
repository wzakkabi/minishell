/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 02:51:22 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/11/02 00:44:31 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*expand_path(char *path, t_env *env)
{
	char	*ret;
	char	*tmp;

	ret = NULL;
	if (path[0] == '~')
	{
		if (path[1] == '/')
		{
			tmp = get_env_var(env, "HOME")->value;
			ret = ft_strjoin(tmp, path + 1);
		}
		else if (path[1] == '\0')
			ret = ft_strdup(get_env_var(env, "HOME")->value);
	}
	return (ret);
}

char	*parse_path(char	**cmd, t_env *env)
{
	int		i;
	char	*tmp;
	char	*ret = NULL;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
	{
		tmp = ft_strjoin("cd: string not in pwd: ", cmd[1]);
		ft_putstr_fd(tmp, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		free(tmp);
		return (NULL);
	}
	else if (i == 2)
	{
		if (ft_strncmp(cmd[1], "~", 1) == 0)
			ret = expand_path(cmd[1], env);
		else 
			ret = ft_strdup(cmd[1]);
	}
	else if (i == 1)
		ret = ft_strdup(get_env_var(env, "HOME")->value);
	return (ret);
}

void	update_pwd_env(char	*old_path, t_env *env)
{
	char	path[PATH_MAX];

	if (old_path == NULL || env == NULL)
		return ;
	update_env_var(env, "OLDPWD", old_path);
	if (getcwd(path, sizeof(path)))
		update_env_var(env, "PWD", path);
	else
		perror("cd: getcwd()");
}

int	cd(t_ast *ast, t_env *env)
{
	char	old_path[PATH_MAX];
	char	*path_to;
	int		i;

	i = 0;
	while (ast->str[i])
		i++;
	if (i > 2)
		return (1);
	if (get_env_var(env, "HOME") == NULL && i < 2)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (1);
	}
	path_to = parse_path(ast->str, env);
	if (getcwd(old_path, sizeof(old_path)) == NULL)
		perror("getcwd()");
	i = chdir(path_to);
	if (i == 0)
	{
		update_pwd_env(old_path, env);
		free(path_to);
	}
	else
		perror("cd");
	return (i);
}
