/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:38:01 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/29 21:13:24 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
int	ft_isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_isalpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

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

