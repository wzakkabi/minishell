/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 04:49:17 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/10/18 04:50:14 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*newnode(void)
{
	t_ast	*new;

	new = (t_ast *)malloc(sizeof(t_ast));
	new->str = (char **)calloc(sizeof(char *), 500);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_lexer	*lxnewnode(void)
{
	t_lexer		*new;
	static int	i;

	i = 0;
	new = (t_lexer *)malloc(sizeof(t_lexer));
	new->num_node = i;
	new->next = NULL;
	new->prev = NULL;
	i++;
	return (new);
}

t_env	*envnode(void)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
