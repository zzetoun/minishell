/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:39:11 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/02 14:20:28 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
