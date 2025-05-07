/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:10:16 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/06 23:11:15 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *ha, const char *ne, size_t len)
{
	size_t	idx;
	size_t	jdx;

	idx = 0;
	if (ne[0] == '\0' || !ne)
		return ((char *)ha);
	if (!ft_strchr(ha, (int)ne[0]) || len < ft_strlen(ne))
		return (NULL);
	else
	{
		while (idx < len)
		{
			jdx = 0;
			while (ne[jdx] && ha[idx + jdx] == ne[jdx] && idx + jdx < len)
				jdx++;
			if (jdx == ft_strlen(ne))
				return ((char *)ha + idx);
			idx++;
		}
		return (NULL);
	}
}
