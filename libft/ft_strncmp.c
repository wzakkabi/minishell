/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:38:47 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/11/02 16:12:14 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	x;
	size_t	len;

	if (!s1)
		return (-1);
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
