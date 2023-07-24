/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:53:06 by wzakkabi          #+#    #+#             */
/*   Updated: 2022/10/02 18:53:06 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	x;
	char	*dst1;
	char	*src1;

	src1 = (char *)src;
	dst1 = (char *)dst;
	x = 0;
	if (!src1 && !dst1)
		return (NULL);
	if (dst1 > src1)
	{
		while (len-- > 0)
		{
			dst1[len] = src1[len];
		}
	}
	else
	{
		while (x < len)
		{
			dst1[x] = src1[x];
			x++;
		}
	}
	return (dst);
}
