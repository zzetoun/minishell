/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:37:59 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/02 14:20:09 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
