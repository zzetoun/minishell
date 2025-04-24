/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 19:36:30 by zzetoun           #+#    #+#             */
/*   Updated: 2025/01/11 19:36:30 by zzetoun          ###   ########.ae       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int		ft_printf(int fd, const char *prnt, ...);
void    linked_list_print(t_env_info  *env, char **_envp, int option);

ssize_t	ft_putchar_fd(const char prnt, int fd);
ssize_t	ft_putstr_fd(char *s, int fd);
ssize_t	ft_putnbr_fd(long num, int fd);

#endif