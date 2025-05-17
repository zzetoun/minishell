/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imickhai <imickhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:36:16 by imickhai          #+#    #+#             */
/*   Updated: 2024/12/18 16:35:43 by imickhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(const char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	if (get_size(needle) == 0)
		return ((char *) haystack);
	if (get_size(haystack) == 0 || len == 0)
		return (NULL);
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		if (haystack[i] == needle[0])
		{
			while (i + j < len && haystack[i + j] == needle[j]
				&& needle[j] != '\0')
				j++;
			if (j == get_size(needle))
				return ((char *) &haystack[i]);
		}
		i++;
	}
	return (NULL);
}
