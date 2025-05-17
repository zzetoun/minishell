/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imickhai <imickhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:50:29 by imickhai          #+#    #+#             */
/*   Updated: 2024/12/18 20:24:40 by imickhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t		i;
	char		symb;

	symb = (char) c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == symb)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == symb)
		return ((char *) &s[i]);
	return (NULL);
}
