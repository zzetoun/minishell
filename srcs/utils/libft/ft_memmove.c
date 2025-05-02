/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:38:30 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/02 14:20:54 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*_src;
	unsigned char	*_dst;
	size_t			i;

	if (!dst && !src)
		return (NULL);
	_dst = (unsigned char *)dst;
	_src = (unsigned char *)src;
	i = 0;
	if (dst > src)
	{
		while (len--)
			_dst[len] = _src[len];
	}
	else
	{
		while (len--)
		{
			_dst[i] = _src[i];
			i++;
		}
	}
	return (dst);
}
