/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:02:56 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/24 14:10:19 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_array_len(char **str)
{
	size_t	size;

	size = 0;
	if (!str || !*str)
		return (0);
	while (str[size])
		size++;
	return (size);
}
