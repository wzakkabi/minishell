/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:39:24 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/03/14 01:45:46 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_word(char const *s, char c)
{
	int	x;
	int	word;

	word = 0;
	x = 0;
	while (s[x] != '\0')
	{
		if (s[x] == c)
			x++;
		else
		{
			word++;
			while (s[x] != c && s[x] != '\0')
				x++;
		}
	}
	return (word);
}

static	void	ft_crt(char const *s, char c, char **p)
{
	int	y;
	int	x;
	int	wd;
	int	word;

	x = 0;
	y = 0;
	wd = 0;
	word = ft_word(s, c);
	while (wd < word)
	{
		while (s[x] == c && s[x] != '\0')
			x++;
		if (s[x] != c && s[x - 1] == c)
			y = x;
		while (s[x] != c && s[x] != '\0')
			x++;
		p[wd] = ft_substr(s, y, x - y);
		wd++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		word;

	if (!s)
		return (NULL);
	word = ft_word(s, c);
	p = ft_calloc((word + 1), sizeof(char *));
	if (!p)
		return (NULL);
	ft_crt(s, c, p);
	return (p);
}
