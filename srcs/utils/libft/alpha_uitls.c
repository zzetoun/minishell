/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha_uitls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:12:16 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/19 20:34:34 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isalpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}
char	*str_tolower(char *s)
{
	int	i;
	
	if (!s)
		return (NULL);
	i = -1;
	while(s[++i])
		if (s[i] >= 65 && s[i] <= 90)
			s[i] += 32;
	return (s);
}

