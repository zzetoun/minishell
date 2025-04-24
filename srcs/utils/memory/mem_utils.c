/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:03:17 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/25 03:57:21 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"

void	*ft_calloc(size_t counter, size_t size)
{
	unsigned char	*s;
	void			*ptr;
	size_t			n;

	if (size && counter > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(size * counter);
	if (!ptr)
		return (NULL);
	s = (unsigned char *)ptr;
	n = size * counter;
	while (n > 0)
	{
		*s = 0;
		s++;
		n--;
	}
	return (ptr);
}

void	*ft_memset(void *b, int n, size_t len)
{
	unsigned char	*a;
	size_t			i;

	a = b;
	i = -1;
	while (++i < len)
		a[i] = n;
	return (b);
}

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
