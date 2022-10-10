/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:17:32 by ysalmi            #+#    #+#             */
/*   Updated: 2022/10/10 12:52:43 by ysalmi           ###   ########.fr       */
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
		rest[0] = 0;
		ret = read_next_line(fd, &line, rest, &realloc);
		if (!ret || (ret == 1 && !*line))
			return (0);
		else if (ret == 1)
			return (line);
	}
}

/*
 *	return:
 *		0: allocation error
 *		1: finished reading line
 *		2: still need to read more
 */

int	read_next_line(int fd, char **line, char *rest, int *realloc)
{
	int		ret;
	char	buff[READ_BUFF_SIZE];

	ret = read(fd, buff, READ_BUFF_SIZE);
	if (ret > 0)
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
	return (1);
}

char	*concat(char *dst, char *src, int *realloc, char *rest)
{
	int	dst_size;
	int	dst_len;
	int	src_max;
	int	pos;

	dst_size = (*realloc + 1) * LINE_MIN_SIZE;
	dst_len = ft_strlen(dst);
	src_max = READ_BUFF_SIZE;
	pos = ft_strchr(src, '\n', READ_BUFF_SIZE);
	if (dst_size - dst_len < src_max)
		dst = ft_realloc(dst, realloc);
	if (!dst)
		return (0);
	if (pos >= 0)
	{
		ft_strcat(dst, src, 0, pos + 1);
		rest[0] = 0;
		ft_strcat(rest, src, pos + 1, READ_BUFF_SIZE);
		*realloc = -1;
	}
	else
		ft_strcat(dst, src, 0, READ_BUFF_SIZE);
	return (dst);
}

char	*ft_realloc(char *s, int *realloc)
{
	char	*r;

	*realloc += 1;
	r = ft_calloc((*realloc + 1) * LINE_MIN_SIZE);
	if (!r)
		return (0);
	ft_strcat(r, s, 0, ft_strlen(s));
	free(s);
	return (r);
}

void	ft_strcat(char *dst, char *src, int start, int stop)
{
	int	i;
	int	len;

	len = ft_strlen(dst);
	i = start;
	while (src[i] && i < stop)
	{
		dst[len++] = src[i];
		i++;
	}
	dst[len] = 0;
}
