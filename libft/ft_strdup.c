/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 01:16:35 by wzakkabi          #+#    #+#             */
/*   Updated: 2022/10/08 03:35:06 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	int		x;

	x = 0;
	p = ft_calloc(ft_strlen((char *)s1) + 1, sizeof(char));
	if (!(p))
		return (NULL);
	while (s1[x])
	{
		p[x] = s1[x];
		x++;
	}
	return (p);
}
