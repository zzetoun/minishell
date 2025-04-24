/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_uti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 19:35:21 by zzetoun           #+#    #+#             */
/*   Updated: 2025/01/11 19:35:21 by zzetoun          ###   ########.ae       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

ssize_t	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

ssize_t	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		s = "(null)";
	return (write(fd, s, ft_strlen(s)));
}

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

void linked_list_print(t_env_info  *env, char **_envp, int option)
{
    t_envp *envp;
    int    idx;

    envp = env->head;
    idx = 0;
    ft_printf(1, "env size: {%d}\n",env->size);
    while(envp)
    {
        if (option == 1)
        {
            ft_printf(1, "[%d] envp->str: {%s}\n",envp->idx, envp->str);
            ft_printf(1, "[%d] _envp: {%s}\n", idx, _envp[idx]);
        }
        else
            break ;
        idx++;
        envp = envp->next;
    }
}
