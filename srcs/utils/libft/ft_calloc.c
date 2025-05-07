/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:14:03 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/07 18:14:07 by zzetoun          ###   ########.fr       */
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
