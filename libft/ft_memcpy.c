/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imickhai <imickhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:17:58 by imickhai          #+#    #+#             */
/*   Updated: 2024/12/18 18:51:09 by imickhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*ptr_dest;
	const unsigned char	*ptr_src;
	size_t				i;

	ptr_dest = dst;
	ptr_src = src;
	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n-- > 0)
	{
		ptr_dest[i] = ptr_src[i];
		i++;
	}
	return (dst);
}
