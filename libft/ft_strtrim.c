/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imickhai <imickhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:54:27 by imickhai          #+#    #+#             */
/*   Updated: 2024/12/23 17:02:04 by imickhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(char const *str)
{
	int		i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	i;
	size_t	start;
	size_t	end;

	i = 0;
	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	if (s1[start] == '\0')
		return (ft_strdup(""));
	end = get_size(s1) - 1;
	while (end > start && ft_strchr(set, s1[end]))
		end--;
	result = malloc((end - start + 2) * sizeof(char));
	if (!result)
		return (NULL);
	while (start <= end)
		result[i++] = s1[start++];
	result[i] = '\0';
	return (result);
}
