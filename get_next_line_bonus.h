/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:05:11 by ysalmi            #+#    #+#             */
/*   Updated: 2022/10/09 15:55:21 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define LINE_MIN_SIZE 128
# define READ_BUFF_SIZE 1

char	*get_next_line(int fd);
char	*concat(char *dst, char *src, int *relloc, char *rest);
char	*ft_realloc(char *s, int *realloc);
int		strcat_c(char *dst, char *src, int stop);

void	*ft_calloc(int n);
int		ft_strlen(char *s);
#endif
