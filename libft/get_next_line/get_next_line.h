/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:25:23 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/11/03 09:03:47 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000000000
# endif

char	*get_next_line(int fd);
char	*nwline(char *p);
char	*cutline(char *p);
char	*fstrchr(char *s, int c);
int		fstrlen(char *p);
char	*fstrjoin(char *save, char *buf, int count);

#endif