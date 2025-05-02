/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:33:51 by zzetoun           #+#    #+#             */
/*   Updated: 2024/07/04 19:23:02 by zzetoun          ###   ########.ae       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	size;

	if (dstsize == 0)
		return (ft_strlen(src));
	size = ft_strlen(dst);
	if (size < dstsize - 1)
		ft_strlcpy(dst + size, src, dstsize - size);
	if (size >= dstsize)
		size = dstsize;
	return (size + ft_strlen(src));
}
