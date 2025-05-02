/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:38:32 by zzetoun           #+#    #+#             */
/*   Updated: 2024/07/08 22:09:31 by zzetoun          ###   ########.ae       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_numblen(int n)
{
	int	numblen;

	if (n == 0)
		return (1);
	numblen = 0;
	while (n != 0)
	{
		n /= 10;
		numblen++;
	}
	return (numblen);
}

static int	ft_assign(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	char	sign;

	sign = '-' * (n < 0);
	len = ft_numblen(n) + (sign == '-') + 1;
	str = malloc(sizeof(char) * len--);
	if (!str)
		return (NULL);
	str[len--] = '\0';
	while (len != -1)
	{
		if (len == 0 && sign == '-')
			str[len--] = '-';
		else
			str[len--] = ft_assign(n % 10) + '0';
		n /= 10;
	}
	return (str);
}
