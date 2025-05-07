/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:06:10 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/07 18:06:17 by zzetoun          ###   ########.fr       */
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
