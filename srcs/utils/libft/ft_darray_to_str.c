/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darray_to_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:14:03 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 15:17:21 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_darray_to_str(char **darray, char *seperator)
{
	char	*str;
	int		idx;

	if (!darray || !*darray)
		return (NULL);
	idx = -1;
	str = NULL;
	while (darray[++idx])
	{
		if (idx == 0)
			str = ft_strdup(darray[idx]);
		else
			str = ft_strjoin_free(str, darray[idx]);
		if (darray[idx + 1])
			str = ft_strjoin_free(str, seperator);
	}
	return (str);
}
