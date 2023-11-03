/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:39:03 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/02/23 22:05:22 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	find_new_line(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

void	fill_holder(int fd, char **holder, int *count)
{
	char	*str;

	while (!find_new_line(*holder) && *count != 0)
	{
		str = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!str)
			break ;
		*count = read(fd, str, BUFFER_SIZE);
		if (*count < 0 || (*count == 0 && !(*holder)))
		{
			if (*holder)
			{
				free(*holder);
				*holder = NULL;
			}
			free(str);
			break ;
		}
		str[*count] = '\0';
		if (*str)
		{
			*holder = strjoin_hlpr(*holder, str);
		}
		free(str);
	}
}

char	*extract_ligne(char **str)
{
	char	*ret;
	char	*tmp;
	int		pos;

	ret = NULL;
	pos = find_new_line(*str);
	if ((*str)[pos] == '\n')
	{
		ret = substr_hlpr(*str, 0, pos + 1);
		tmp = strdup_hlpr(*str);
		free(*str);
		*str = substr_hlpr(tmp, pos + 1, strlen_hlpr(tmp) - pos);
		free(tmp);
		if (**str == '\0')
		{
			free(*str);
			*str = NULL;
		}
		return (ret);
	}
	ret = strdup_hlpr(*str);
	free(*str);
	*str = NULL;
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*holder;
	char		*ret;
	int			count;

	ret = NULL;
	if (fd < 0 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (holder)
			free(holder);
		holder = NULL;
		return (NULL);
	}
	count = 1;
	fill_holder(fd, &holder, &count);
	if (!holder)
		return (NULL);
	if (*holder == '\0')
	{
		free(holder);
		return (holder = NULL);
	}
	ret = extract_ligne(&holder);
	return (ret);
}

// int main()
// {
// 	int		fd = open("./alternate_line_nl_no_nl", O_RDONLY);
// 	char	*line;

// 	line = get_next_line(fd);
// 	printf("%s\n", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("%s\n", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("%s\n", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("%s\n", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("%s\n", line);
// 	free(line);
// }
