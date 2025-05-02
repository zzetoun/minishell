/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:14:27 by zzetoun           #+#    #+#             */
/*   Updated: 2024/07/06 19:35:11 by zzetoun          ###   ########.ae       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_head(const char *s1, const char *set)
{
	int		head;
	size_t	idx;

	head = 0;
	idx = 0;
	while (s1[head] && idx < ft_strlen(set))
	{
		if (set[idx] != s1[head])
			idx++;
		else
		{
			idx = 0;
			head++;
		}
	}
	return (head);
}

static int	check_tail(const char *s1, const char *set, int head, int tail)
{
	size_t	idx;

	idx = 0;
	while (tail > head && idx < ft_strlen(set))
	{
		if (set[idx] != s1[tail - 1])
			idx++;
		else
		{
			idx = 0;
			tail--;
		}
	}
	return (tail);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*str;
	int		tail;
	int		head;
	int		sdx;

	if (!s1 || !set)
		return (NULL);
	head = check_head(s1, set);
	tail = check_tail(s1, set, head, (int)ft_strlen(s1)) - head;
	str = malloc(sizeof(char) * (tail + 1));
	if (!str)
		return (NULL);
	sdx = 0;
	while (tail-- > 0)
		str[sdx++] = s1[head++];
	str[sdx] = '\0';
	return (str);
}
