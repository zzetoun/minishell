/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:06:23 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/25 19:01:47 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	idx;

	if (!s)
		return (NULL);
	if (!(unsigned char)c)
		return ((char *)&s[ft_strlen(s)]);
	idx = 0;
	while (s[idx] != '\0')
	{
		if (s[idx] == (unsigned char)c)
			return ((char *)&s[idx]);
		idx++;
	}
	return (NULL);
}
