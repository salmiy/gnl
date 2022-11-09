/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:17:32 by ysalmi            #+#    #+#             */
/*   Updated: 2022/11/09 15:50:15 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define MIN 128

char	*get_next_line(int fd)
{
	static char	rest[BUFFER_SIZE];
	t_chunk		*first;
	int			n;
	int			size;

	if (fd < 0 || fd == 1 || fd == 2)
		return (0);
	if (ft_strchr(rest, '\n', BUFFER_SIZE) > -1)
		return (line_from_rest(rest));
	size = BUFFER_SIZE;
	size = size * (size >= MIN) + ( size * (MIN / size) ) * (size < MIN);
	n = 0;
	first = read_chunks(fd, &n, size);
	if (!first)
		return (0);
	return (line_from_chunk(rest, first, n, size));
}

t_chunk	*read_chunks(int fd, int *i, int size)
{
	t_chunk	*first;
	t_chunk	*curs;
	int		r;	int		end;

	curs = new_chunk(size + 1);
	first = curs;
	end = 0;
	*i += 1;
	while (*i)
	{
		if (!curs)
			return ((t_chunk *)clear_chunks(first));
		curs->next = 0;
		r = read(fd, &curs->content[end], BUFFER_SIZE);
		if (r >= 0)
			curs->content[end + r] = 0;
		else
			curs->content[0] = 0;
		end = (end + r) * (end + r < size);
		if (r < BUFFER_SIZE || ft_strchr(curs->content, '\n', BUFFER_SIZE) > -1)
			break ;
		if (!end)
			curs->next = new_chunk(size + 1);
		if (!end)
			curs = curs->next;
		if (!end)
			*i += 1;
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

char	*line_from_chunk(char *rest, t_chunk *first, int n, int size)
{
	char	*line;
	t_chunk	*curs;
	int		pos;

	if (n == 1 && !first->content[0] && !rest[0])
		return (clear_chunks(first));
	line = malloc((size_t) n * size + ft_strlen(rest) + 1);
	if (!line)
		return (0);
	line[0] = 0;
	concat(line, rest, BUFFER_SIZE);
	curs = first;
	while (curs->next)
	{
		concat(line, curs->content, size + 1);
		curs = curs->next;
	}
	pos = ft_strchr(curs->content, '\n', size + 1);
	pos = pos * (pos > -1) + size * (pos < 0);
	concat(line, curs->content, pos);
	rest[0] = 0;
	if (pos < size)
		concat(rest, &curs->content[pos], size - pos + 1);
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
