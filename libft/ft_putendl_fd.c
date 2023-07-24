/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:23:07 by wzakkabi          #+#    #+#             */
/*   Updated: 2022/10/17 17:59:55 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	int	x;

	x = 0;
	if (!s)
		return ;
	while (s[x])
	{
		write(fd, &s[x], 1);
		x++;
	}
	write(fd, "\n", 1);
}
