/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:17:32 by ysalmi            #+#    #+#             */
/*   Updated: 2022/10/11 19:57:12 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	rest[CHUNK_SIZE];
	t_chunk		*first;
	t_chunk		*curs;
	int			ret;
	int			i;

	if (ft_strchr(rest, '\n', CHUNK_SIZE) > -1)
		return (line_from_rest(rest));
	curs = malloc(sizeof(t_chunk));
	first = curs;
	i = 0;
	while (++i)
	{
		if (!curs)
			return (clear_chunks(first));
		curs->next = 0;
		ret = read(fd, curs->content, CHUNK_SIZE);
		if (ret < CHUNK_SIZE)
			curs->content[ret * (ret >= 0)] = 0;
		if (ret < 1 || ft_strchr(curs->content, '\n', CHUNK_SIZE) > -1)
			break ;
		curs->next = malloc(sizeof(t_chunk));
		curs = curs->next;
	}
	return (line_from_chunk(rest, first, i));
}

char	*line_from_rest(char *rest)
{
	int		pos;
	char	*line;

	pos = ft_strchr(rest, '\n', CHUNK_SIZE);
	line = malloc(pos + 1);
	if (!line)
		return (0);
	line[0] = 0;
	concat(line, rest, pos);
	rest[0] = 0;
	concat(rest, &rest[pos], CHUNK_SIZE - pos);
	return (line);
}

char	*line_from_chunk(char *rest, t_chunk *first, int n)
{
	char	*line;
	t_chunk	*curs;
	int		pos;

	if (n == 1 && !first->content[0])
		return (clear_chunks(first));
	line = malloc((size_t) n * CHUNK_SIZE + ft_strlen(rest));
	if (!line)
		return (0);
	line[0] = 0;
	concat(line, rest, CHUNK_SIZE);
	curs = first;
	while (curs->next)
	{
		concat(line, curs->content, CHUNK_SIZE);
		curs = curs->next;
	}
	pos = ft_strchr(curs->content, '\n', CHUNK_SIZE);
	concat(line, curs->content, pos);
	rest[0] = 0;
	concat(rest, &curs->content[pos], CHUNK_SIZE - pos);
	clear_chunks(first);
	if (!*line)
		return (0);
	return (line);
}

void	concat(char *dst, char *src, int len)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(dst);
	while (src[i] && i < len)
		dst[j++] = src[i++];
	dst[j] = 0;
}

char	*clear_chunks(t_chunk *first)
{
	t_chunk	*aux;

	while (first)
	{
		aux = first->next;
		free(first);
		first = aux;
	}
	return (0);
}
