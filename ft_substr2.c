/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toor <toor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 00:16:49 by toor              #+#    #+#             */
/*   Updated: 2023/08/18 00:26:56 by toor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr2(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	x;
	size_t	u;

	if (!s)
		return (NULL);
	u = len;
	x = 0;
	if (len > ft_strlen(s))
		u = ft_strlen(s);
	p = ft_calloc((u + 1), 1);
	if (!p)
		return (0);
	if (start <= ft_strlen(s))
	{
		while (x < len && start < u)
			p[x++] = s[start++];
	}
	return (p);
}
