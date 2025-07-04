/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:14:21 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/07 18:14:26 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long long	nb;
	int					sign;

	nb = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = 1 - 2 * (*str == '-');
	str += (*str == '-' || *str == '+');
	while (*str >= '0' && *str <= '9')
		nb = (10 * nb) + *(str++) - '0';
	if (nb >= LLONG_MAX && sign == -1)
		return (0);
	else if (nb >= LLONG_MAX)
		return (-1);
	return ((int)nb * sign);
}
