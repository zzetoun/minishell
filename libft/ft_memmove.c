/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imickhai <imickhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:36:18 by imickhai          #+#    #+#             */
/*   Updated: 2024/12/18 15:04:32 by imickhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*ptr_dest;
	const unsigned char	*ptr_src;
	size_t				i;

	ptr_dest = (unsigned char *) dst;
	ptr_src = (const unsigned char *) src;
	i = 0;
	if (ptr_dest == ptr_src || len == 0)
		return (dst);
	if (ptr_dest < ptr_src)
	{
		while (i < len)
		{
			ptr_dest[i] = ptr_src[i];
			i++;
		}
	}
	else
	{
		while (len-- > 0)
			ptr_dest[len] = ptr_src[len];
	}
	return (dst);
}
