/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:17:32 by ysalmi            #+#    #+#             */
/*   Updated: 2022/11/05 12:06:51 by ysalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strchr(char *s, char c, int len)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c && i < len)
		i++;
	if (i == len || (i == 0 && s[i] != c) || !s[i])
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
	while (src[i] && i < len)
		dst[j++] = src[i++];
	dst[j] = 0;
}
