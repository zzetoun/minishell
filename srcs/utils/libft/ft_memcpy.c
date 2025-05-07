/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:10:43 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/07 18:10:49 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;
	size_t			idx;

	idx = -1;
	tmp1 = (unsigned char *)dst;
	tmp2 = (unsigned char *)src;
	if (!tmp1 && !tmp2)
		return (NULL);
	while (++idx < n)
		tmp1[idx] = tmp2[idx];
	return (dst);
}
