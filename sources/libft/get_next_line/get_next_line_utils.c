/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:39:44 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/02/11 18:45:17 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	strlen_hlpr(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*strchr_hlpr(const char *s, int c)
{
	unsigned char	*ret;

	ret = (unsigned char *)s;
	while (1)
	{
		if (*ret == (unsigned char) c)
			return ((char *) ret);
		if (*ret == 0)
			return (NULL);
		ret++;
	}
}

char	*substr_hlpr(const char *s, int start, int len)
{
	int		i;
	char	*ret;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= strlen_hlpr(s))
	{
		ret = (char *) malloc(sizeof(char));
		*ret = '\0';
		return (ret);
	}
	if (len > strlen_hlpr(s) - start)
		len = strlen_hlpr(s) - start;
	s = s + start;
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (*s && i < len)
	{
		ret[i] = *s++;
		i++;
	}
	ret[len] = '\0';
	return (ret);
}

// char	*strtrim_hlpr(char const *s1, char const *set)
// {
// 	char	*ret;
// 	size_t	start;
// 	size_t	len_s1;

// 	if (!s1 || !set)
// 		return (NULL);
// 	len_s1 = strlen_hlpr(s1) - 1;
// 	start = 0;
// 	while ((strchr_hlpr(set, s1[start]) != NULL) && s1[start])
// 		start++;
// 	if (s1[start] == '\0')
// 	{
// 		ret = malloc(sizeof(char));
// 		*ret = '\0';
// 		return (ret);
// 	}
// 	while ((strchr_hlpr(set, s1[len_s1]) != NULL) && (len_s1 >= 0))
// 		len_s1--;
// 	ret = substr_hlpr(s1, start, len_s1 - start + 1);
// 	return (ret);
// }
char	*strdup_hlpr(char *str)
{
	int		i;
	char	*ret;

	ret = malloc((strlen_hlpr(str) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*strjoin_hlpr(char *s1, char *s2)
{
	size_t	i;
	size_t	len;
	char	*ret;

	if (!s2)
		return (NULL);
	if (!s1)
		return (strdup_hlpr(s2));
	len = strlen_hlpr(s1) + strlen_hlpr(s2);
	ret = (char *) malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		*(ret++) = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
		*(ret++) = s2[i++];
	*ret = '\0';
	ret -= len;
	free(s1);
	return (ret);
}
