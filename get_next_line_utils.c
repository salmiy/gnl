/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:17:32 by ysalmi            #+#    #+#             */
/*   Updated: 2022/10/11 19:51:01 by ysalmi           ###   ########.fr       */
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
