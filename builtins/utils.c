/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 02:56:15 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/11/04 11:13:49 by mbousbaa         ###   ########.fr       */
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
			if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
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
		if (ft_strncmp(tmp->key, "?", 2) != 0)
			tmp->print_or_not = 1;
		else
			tmp->print_or_not = 0;
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
	if (ft_strncmp(curr->key, key, ft_strlen(key) + 1) == 0)
	{
		*env = curr->next;
		delete_node(curr);
		return (1);
	}
	while (curr)
	{
		if (ft_strncmp(curr->key, key, ft_strlen(key) + 1) == 0)
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

	if (!env || !key)
		return (0);
	env_p = *env;
	while (env_p->next != NULL)
		env_p = env_p->next;
	if (env_p->next == NULL)
	{
		env_p->next = malloc(sizeof(t_env));
		env_p = env_p->next;
		env_p->key = ft_strdup(key);
		if (!value)
			env_p->value = NULL;
		else
			env_p->value = ft_strdup(value);
		if (ft_strncmp(key, "?", 2) != 0)
			env_p->print_or_not = 1;
		else
			env_p->print_or_not = 0;
		env_p->next = NULL;
		return (1);
	}
	return (0);
}
