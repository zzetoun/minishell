/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:12:25 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/06 23:12:27 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	idx;

	idx = -1;
	if (!s1 || !s2)
		return (-1);
	while (++idx < n && s1[idx] && s2[idx])
		if (s1[idx] != s2[idx])
			return (((unsigned char *)s1)[idx] - ((unsigned char *)s2)[idx]);
	if (idx < n)
		return (((unsigned char *)s1)[idx] - ((unsigned char *)s2)[idx]);
	return (0);
}
