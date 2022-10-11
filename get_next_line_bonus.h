/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:05:11 by ysalmi            #+#    #+#             */
/*   Updated: 2022/10/11 19:58:10 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define MAX_DESCRIPTORS 20
# define CHUNK_SIZE 128

typedef struct s_chunk
{
	struct s_chunk	*next;
	char			content[CHUNK_SIZE];
}	t_chunk;

char	*get_next_line(int fd);
char	*line_from_rest(char *rest);
char	*line_from_chunk(char *rest, t_chunk *first, int n);
char	*clear_chunks(t_chunk *first);
void	concat(char *dst, char *src, int len);

int		ft_strchr(char *s, char c, int len);
int		ft_strlen(char *s);
#endif
