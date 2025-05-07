/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:07:32 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/07 18:07:34 by zzetoun          ###   ########.fr       */
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
