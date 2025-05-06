/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:57:50 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/06 16:57:50 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_print(int fd, const char prnt, va_list args)
{
	if (prnt == 'd' || prnt == 'i')
		ft_putnbr_fd(va_arg(args, int), fd);
	if (prnt == 'c')
		ft_putchar_fd((char)va_arg(args, int), fd);
	if (prnt == 's')
		ft_putstr_fd(va_arg(args, char *), fd);
	if (prnt == '%')
		ft_putchar_fd('%', fd);
}

void	ft_printf(int fd, const char *prnt, ...)
{
	va_list		args;

	if (!prnt)
		return ;
	va_start(args, prnt);
	while (*prnt)
	{
		if (*prnt == '%' && *(prnt + 1))
		{
			ft_print(fd, *++prnt, args);
			prnt++;
		}
		else
			ft_putchar_fd(*prnt++, fd);
	}
	va_end(args);
}
