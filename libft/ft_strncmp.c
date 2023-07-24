/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:38:47 by wzakkabi          #+#    #+#             */
/*   Updated: 2022/10/19 02:19:07 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	x;
	size_t	len;

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
