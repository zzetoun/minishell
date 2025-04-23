/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:21:53 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/20 21:34:36 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

int		ft_isdigit(int c);
int		ft_isspace(int c);
int	    ft_isalnum(int c);
int     ft_isalpha(int c);
int		ft_atoi(const char *str, int *error);

char    *str_tolower(char *s);

#endif