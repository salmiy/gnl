/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:05:11 by ysalmi            #+#    #+#             */
/*   Updated: 2022/11/09 15:50:10 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

typedef struct s_chunk
{
	struct s_chunk	*next;
	char			*content;
}	t_chunk;

char	*get_next_line(int fd);
char	*line_from_rest(char *rest);
t_chunk	*read_chunks(int fd, int *i, int size);
char	*line_from_chunk(char *rest, t_chunk *first, int n, int size);
t_chunk	*new_chunk(int size);
void	*clear_chunks(t_chunk *first);
void	concat(char *dst, char *src, int len);

int		ft_strchr(char *s, char c, int len);
int		ft_strlen(char *s);

#endif
