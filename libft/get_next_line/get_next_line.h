/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:25:23 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/11/03 16:08:57 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000000
# endif
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
int		strlen_hlpr(const char *s);
char	*substr_hlpr(const char *s, int start, int len);
char	*strchr_hlpr(const char *s, int c);
char	*strdup_hlpr(char *str);
char	*strjoin_hlpr(char *s1, char *s2);
#endif
