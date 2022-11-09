/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:17:32 by ysalmi            #+#    #+#             */
/*   Updated: 2022/11/09 14:55:34 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_chunk	*read_chunks(int fd, int *i);

char	*get_next_line(int fd)
{
	static char	rest[BUFFER_SIZE];
	t_chunk		*first;
	int			n;

	if (fd < 0 || fd == 1 || fd == 2)
		return (0);
	if (ft_strchr(rest, '\n', BUFFER_SIZE) > -1)
		return (line_from_rest(rest));
	n = 0;
	first = read_chunks(fd, &n);
	if (!first)
		return (0);
	return (line_from_chunk(rest, first, n));
}

t_chunk	*new_chunk(void)
{
	t_chunk	*new;

	new = malloc(sizeof(t_chunk));
	if (new)
	{
		new->content = malloc(BUFFER_SIZE);
		if (new->content)
			return (new);
		free(new);
		return (0);
	}
	return (0);
}

t_chunk	*read_chunks(int fd, int *i)
{
	t_chunk	*first;
	t_chunk	*curs;
	int		r;

	curs = new_chunk();
	first = curs;
	while (++(*i))
	{
		if (!curs)
			return ((t_chunk *)clear_chunks(first));
		curs->next = 0;
		r = read(fd, curs->content, BUFFER_SIZE);
		if (r < BUFFER_SIZE)
			curs->content[r * (r > 0)] = 0;
		if (r < BUFFER_SIZE || ft_strchr(curs->content, '\n', BUFFER_SIZE) > -1)
			break ;
		curs->next = new_chunk();
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

void	*clear_chunks(t_chunk *first)
{
	t_chunk	*aux;

	while (first)
	{
		aux = first->next;
		free(first->content);
		free(first);
		first = aux;
	}
	return (0);
}
