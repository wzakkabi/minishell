/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:08:05 by wzakkabi          #+#    #+#             */
/*   Updated: 2022/10/18 23:21:19 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*p;
	int		x;

	if (!s)
		return (NULL);
	p = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!p)
		return (NULL);
	x = 0;
	while (s[x])
	{
		p[x] = f(x, s[x]);
		x++;
	}
	return (p);
}
