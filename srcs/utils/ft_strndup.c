/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:18:13 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/08 16:04:22 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strndup(const char *str, size_t n)
{
    char *dup;
    size_t len;

    if (!str)
        return (NULL);
    len = ft_strlen(str);
    if (len > n)
        len = n;
    dup = malloc(len + 1);
    if (!dup)
        return (NULL);
    strncpy(dup, str, len + 1);
    return (dup);
}
