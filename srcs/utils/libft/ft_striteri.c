/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:24:00 by zzetoun           #+#    #+#             */
/*   Updated: 2024/07/09 16:24:02 by zzetoun          ###   ########.ae       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	len;
	unsigned int	idx;

	if (!s || !f)
		return ;
	idx = 0;
	len = (unsigned int)ft_strlen(s);
	while (idx < len)
	{
		f(idx, &s[idx]);
		idx++;
	}
}
