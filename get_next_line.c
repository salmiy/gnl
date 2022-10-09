/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:17:32 by ysalmi            #+#    #+#             */
/*   Updated: 2022/10/09 16:27:26 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_next_line(int fd, char **line, char *rest, int *realloc);

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	int			realloc;
	int			ret;

	line = ft_calloc(LINE_MIN_SIZE);
	if (!rest)
		rest = ft_calloc(READ_BUFF_SIZE);
	if (!line || !rest)
		return (0);
	realloc = 0;
	line = concat(line, rest, &realloc, rest);
	if (realloc == -1)
		return (line);
	while (1)
	{
		ret = read_next_line(fd, &line, rest, &realloc);
		if (!ret)
			return (0);
		else if (ret == 1)
			return (line);
		else if (ret < 0)
			return (0);
	}
}

int	read_next_line(int fd, char **line, char *rest, int *realloc)
{
	int		ret;
	char	buff[READ_BUFF_SIZE];

	ret = read(fd, buff, READ_BUFF_SIZE);
	if (ret)
	{
		if (ret < READ_BUFF_SIZE)
			buff[ret] = 0;
		*line = concat(*line, buff, realloc, rest);
		if (!line)
			return (0);
		if (*realloc == -1)
			return (1);
		return (2);
	}
	else
		return (-1);
}

char	*concat(char *dst, char *src, int *realloc, char *rest)
{
	int	dst_size;
	int	dst_len;
	int	src_max;
	int	crsr;

	dst_size = (*realloc + 1) * LINE_MIN_SIZE;
	dst_len = ft_strlen(dst);
	src_max = READ_BUFF_SIZE;
	if (dst_size - dst_len < src_max)
		dst = ft_realloc(dst, realloc);
	if (!dst)
		return (0);
	crsr = strcat_c(dst, src, READ_BUFF_SIZE);
	if (crsr > -1 && src[crsr - 1])
	{
		rest[0] = 0;
		strcat_c(rest, &src[crsr], READ_BUFF_SIZE - crsr);
		*realloc = -1;
	}
	return (dst);
}

char	*ft_realloc(char *s, int *realloc)
{
	char	*r;

	*realloc += 1;
	r = ft_calloc((*realloc + 1) * LINE_MIN_SIZE);
	if (!r)
		return (0);
	strcat_c(r, s, ft_strlen(s));
	free(s);
	return (r);
}

int	strcat_c(char *dst, char *src, int stop)
{
	int	i;
	int	len;

	len = ft_strlen(dst);
	i = 0;
	while (i < stop)
	{
		if (stop == READ_BUFF_SIZE && src[i] == '\n')
		{
			dst[len + i] = src[i];
			dst[len + ++i] = 0;
			return (i);
		}
		dst[len + i] = src[i];
		i++;
	}
	dst[len + i] = 0;
	return (-1);
}
