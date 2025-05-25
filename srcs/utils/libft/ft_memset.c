/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:08:34 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/25 17:04:50 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int n, size_t len)
{
	unsigned char	*a;
	size_t			idx;

	a = b;
	idx = 0;
	while (idx < len)
		a[idx++] = n;
	return (b);
}
