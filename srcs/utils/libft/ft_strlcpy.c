/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:37:07 by zzetoun           #+#    #+#             */
/*   Updated: 2024/07/04 18:31:27 by zzetoun          ###   ########.ae       */
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
