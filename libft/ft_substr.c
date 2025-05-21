/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imickhai <imickhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:22:25 by imickhai          #+#    #+#             */
/*   Updated: 2024/12/23 17:08:51 by imickhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	get_size(char const *s)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static char	*allocate_substr(size_t len)
{
	char	*result;

	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[len] = '\0';
	return (result);
}

char	*ft_substr(const char *s, unsigned int st, size_t l)
{
	size_t			max_len;
	unsigned int	i;
	char			*result;

	i = 0;
	if (!s)
		return (NULL);
	if (st >= get_size(s))
		return (allocate_substr(0));
	max_len = get_size(s) - st;
	if (l > max_len)
		l = max_len;
	result = allocate_substr(l);
	if (!result)
		return (NULL);
	while (i < l)
		result[i++] = s[st++];
	return (result);
}

// char	*ft_substr(char const *s, unsigned int st, size_t l)
// {
// 	size_t			i;
// 	unsigned int	j;
// 	size_t			max_len;
// 	char			*result;

// 	i = 0;
// 	j = st;
// 	if (!s)
//     	return (NULL);
// 	if (st >= get_size(s))
// 	{
// 		result = malloc(1);
// 		if (!result)
// 			return (NULL);
// 		result[0] = '\0';
// 		return (result);
// 	}
// 	max_len = (size_t)get_size(s) - st;
// 	if (l > max_len)
//         l = max_len;
// 	result = malloc((l + 1) * sizeof(char));
// 	if (!result)
// 		return (NULL);
// 	while(i < l)
// 	{
// 		result[i] = s[j];
// 		i++;
// 		j++;
// 	}
// 	result[i] = '\0';
// 	return (result);
// }
