/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:17:32 by ysalmi            #+#    #+#             */
/*   Updated: 2022/11/09 12:37:45 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strchr(char *s, char c, int len)
{
	int	i;

	i = 0;
	while (i < len && s[i] && s[i] != c)
		i++;
	if (i == len || s[i] != c)
		return (-1);
	return (i + 1);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	concat(char *dst, char *src, int len)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(dst);
	while (i < len && src[i])
		dst[j++] = src[i++];
	dst[j] = 0;
}
