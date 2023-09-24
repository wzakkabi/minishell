/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 02:56:15 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/09/01 15:19:25 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*get_env_var(t_env *env, char *key)
{
	t_env	*tmp;

	if (!env)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (tmp->key != NULL)
		{
			if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0
				&& ft_strlen(tmp->key) == ft_strlen(key))
				break ;
		}
		tmp = tmp->next;
	}
	return (tmp);
}

int	update_env_var(t_env *env, char *key, char *value)
{
	t_env	*tmp;

	tmp = get_env_var(env, key);
	if (tmp != NULL)
	{
		free(tmp->value);
		tmp->value = ft_strdup(value);
		return (1);
	}
	return (0);
}

void	delete_node(t_env *node)
{
	if (node)
	{
		free(node->key);
		free(node->value);
		free(node);
	}
}

int	unset_env_var(t_env **env, char *key)
{
	t_env	*curr;
	t_env	*tmp;

	curr = *env;
	tmp = NULL;
	if (ft_strncmp(curr->key, key, ft_strlen(key)) == 0)
	{
		*env = curr->next;
		delete_node(curr);
		return (1);
	}
	while (curr)
	{
		if (ft_strncmp(curr->key, key, ft_strlen(key)) == 0)
			break ;
		tmp = curr;
		curr = curr->next;
	}
	if (curr == NULL)
		return (0);
	tmp->next = curr->next;
	delete_node(curr);
	return (1);
}

int	add_env_var(t_env **env, char *key, char *value)
{
	t_env	*env_p;

	if (!env || !key || !value)
		return (0);
	env_p = *env;
	while (env_p->next != NULL)
		env_p = env_p->next;
	if (env_p->next == NULL)
	{
		env_p->next = malloc(sizeof(t_env));
		env_p = env_p->next;
		env_p->key = ft_strdup(key);
		env_p->value = ft_strdup(value);
		return (1);
	}
	return (0);
}
