/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:17:32 by ysalmi            #+#    #+#             */
/*   Updated: 2022/11/09 12:05:16 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	rest[OPEN_MAX][BUFFER_SIZE];
	t_chunk		*first;
	int			i;

	if (fd < 0 || fd == 1 || fd == 2)
		return (0);
	if (ft_strchr(rest[fd], '\n', BUFFER_SIZE) > -1)
		return (line_from_rest(rest[fd]));
	i = 0;
	first = read_chunks(fd, &i);
	if (!first)
		return (0);
	return (line_from_chunk(rest[fd], first, i));
}

t_chunk	*read_chunks(int fd, int *i)
{
	t_chunk	*first;
	t_chunk	*curs;
	int		r;

	curs = malloc(sizeof(t_chunk));
	first = curs;
	while (++(*i))
	{
		if (!curs)
		{
			clear_chunks(first);
			return (0);
		}
		curs->next = 0;
		r = read(fd, curs->content, BUFFER_SIZE);
		if (r > 0 && r < BUFFER_SIZE)
			curs->content[r] = 0;
		else if (r <= 0)
			curs->content[0] = 0;
		if (r < BUFFER_SIZE || ft_strchr(curs->content, '\n', BUFFER_SIZE) > -1)
			break ;
		curs->next = malloc(sizeof(t_chunk));
		curs = curs->next;
	}
	return (first);
}

char	*line_from_rest(char *rest)
{
	int		pos;
	char	*line;

	pos = ft_strchr(rest, '\n', BUFFER_SIZE);
	line = malloc(pos + 1);
	if (!line)
		return (0);
	line[0] = 0;
	concat(line, rest, pos);
	rest[0] = 0;
	concat(rest, &rest[pos], BUFFER_SIZE - pos);
	return (line);
}

char	*line_from_chunk(char *rest, t_chunk *first, int n)
{
	char	*line;
	t_chunk	*curs;
	int		pos;

	if (n == 1 && !first->content[0] && !rest[0])
		return (clear_chunks(first));
	line = malloc((size_t) n * BUFFER_SIZE + ft_strlen(rest) + 1);
	if (!line)
		return (0);
	line[0] = 0;
	concat(line, rest, BUFFER_SIZE);
	curs = first;
	while (curs->next)
	{
		concat(line, curs->content, BUFFER_SIZE);
		curs = curs->next;
	}
	pos = ft_strchr(curs->content, '\n', BUFFER_SIZE);
	pos = pos * (pos > -1) + BUFFER_SIZE * (pos < 0);
	concat(line, curs->content, pos);
	rest[0] = 0;
	if (pos < BUFFER_SIZE)
		concat(rest, &curs->content[pos], BUFFER_SIZE - pos);
	clear_chunks(first);
	return (line);
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
