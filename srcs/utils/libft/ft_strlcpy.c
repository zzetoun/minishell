/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:12:39 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/06 23:12:41 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	size;

	size = ft_strlen(src);
	if (dstsize <= 0)
		return (size);
	if (size >= dstsize)
		size = dstsize - 1;
	ft_memcpy(dst, src, size);
	dst[size] = '\0';
	return (ft_strlen(src));
}
