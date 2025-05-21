/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imickhai <imickhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:19:22 by imickhai          #+#    #+#             */
/*   Updated: 2024/12/18 18:51:18 by imickhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size(char *restrict dst)
{
	size_t		i;

	i = 0;
	while (dst[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dsts)
{
	size_t		i;
	size_t		dst_len;

	dst_len = get_size(dst);
	i = 0;
	if (dsts == 0)
		return (ft_strlen(src));
	if (dst_len >= dsts)
		return (dsts + ft_strlen(src));
	dsts--;
	while (src[i] != '\0' && dst_len + i < dsts)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + ft_strlen(src));
}
