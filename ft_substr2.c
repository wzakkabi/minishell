/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 00:16:49 by toor              #+#    #+#             */
/*   Updated: 2023/11/03 14:43:41 by wzakkabi         ###   ########.fr       */
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

int	ft_strncmp2(const char *s1, const char *s2, size_t n)
{
	size_t	x;
	size_t	len;

	if (!s1 || !s2)
		return (10);
	len = ft_strlen(s1);
	x = 0;
	while (x < n && x <= len)
	{
		if (s1[x] != s2[x])
		{
			x = ((unsigned char *)s1)[x] -((unsigned char *)s2)[x];
			return (x);
		}
		x++;
	}
	return (0);
}
