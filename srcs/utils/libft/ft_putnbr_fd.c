/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:40:27 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/02 14:36:35 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putnbr_fd(long n, int fd)
{
	ssize_t	number;
	ssize_t	total;
	ssize_t	tmp;

	total = 0;
	if (n < 0)
	{
		if (ft_putchar_fd('-', fd) < 0)
			return (-1);
		n *= -1;
		total++;
	}
	number = n % 10 + '0';
	if (n / 10 > 0)
	{
		tmp = ft_putnbr_fd(n / 10, fd);
		if (tmp < 0)
			return (-1);
		total += tmp;
	}
	if (ft_putchar_fd(number, fd) < 0)
		return (-1);
	total++;
	return (total);
}
