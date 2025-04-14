/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_uti.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:46:27 by zzetoun           #+#    #+#             */
/*   Updated: 2025/02/24 19:46:27 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!(unsigned char)c)
		return ((char *)&s[ft_strlen(s)]);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	idx;

	idx = -1;
	if (!s1 || !s2)
		return (-1);
	while (++idx < n && s1[idx] && s2[idx])
		if (s1[idx] != s2[idx])
			return (((unsigned char *)s1)[idx] - ((unsigned char *)s2)[idx]);
	if (idx < n)
		return (((unsigned char *)s1)[idx] - ((unsigned char *)s2)[idx]);
	return (0);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	i = -1;
	str = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (s[++i])
		str[i] = s[i];
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}
