/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:38:01 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/14 19:53:18 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
int	ft_isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_atoi(const char *str, int *error)
{
	unsigned long long	nb;
	int					sign;

	nb = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = 1 - 2 * (*str == '-');
	str += (*str == '-' || *str == '+');
	while (*str >= '0' && *str <= '9')
	{
		nb = (10 * nb) + *(str++) - '0';
		if ((nb >= LLONG_MAX && sign == -1) || nb > LLONG_MAX)
			*error = 1;
		break ;
	}
	return ((int)nb * sign);
}
