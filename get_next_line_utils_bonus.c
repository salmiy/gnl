/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:17:32 by ysalmi            #+#    #+#             */
/*   Updated: 2022/10/10 11:54:30 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(int n)
{
	void	*r;
	int		i;

	i = -1;
	r = malloc(n);
	if (!r)
		return (0);
	while (++i < n)
		((char *)r)[i] = 0;
	return (r);
}

int	ft_strchr(char *s, char c, int len)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c && i < len)
		i++;
	if (i == len || (i == 0 && s[i] != c) || !s[i])
		return (-1);
	return (i);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
