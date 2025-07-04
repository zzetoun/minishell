/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:06:49 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/25 19:21:24 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_free_split(char **sp_str, int kdx)
{
	while (kdx >= 0)
		free(sp_str[kdx--]);
	free(sp_str);
	return (0);
}

static int	ft_counter(const char *s, char c)
{
	int		counter;
	size_t	idx;

	idx = -1;
	counter = 0;
	while (++idx < ft_strlen(s))
	{
		counter += (s[idx] != c && idx == 0);
		counter += (idx && s[idx] != c && s[idx - 1] == c);
	}
	return (counter);
}

static int	ft_allocate(const char *s, char c, char **sp_str)
{
	int	idx;
	int	jdx;
	int	kdx;

	idx = 0;
	kdx = 0;
	while (s[idx])
	{
		jdx = 0;
		while (s[idx] == c)
			idx++;
		while (s[idx] && s[idx] != c)
		{
			idx++;
			jdx++;
		}
		if (jdx > 0)
			sp_str[kdx] = ft_calloc((jdx + 1), sizeof(char));
		if (jdx > 0 && !sp_str[kdx])
			return (ft_free_split(sp_str, kdx));
		kdx++;
	}
	return (1);
}

static char	**ft_assign(const char *s, char c, char **sp_str)
{
	int		idx;
	int		jdx;
	int		kdx;

	idx = 0;
	jdx = 0;
	while (s[idx])
	{
		kdx = 0;
		while (s[idx] == c)
			idx++;
		while (s[idx] && s[idx] != c)
			sp_str[jdx][kdx++] = s[idx++];
		if (kdx > 0)
			jdx++;
	}
	return (sp_str);
}

char	**ft_split(const char *s, char c)
{
	char	**sp_str;
	int		i;
	int		all_spaces;

	if (!s)
		return (NULL);
	all_spaces = 1;
	i = -1;
	while (s[++i])
		if (s[i] != ' ')
			all_spaces = 0;
	if (!s[0] || all_spaces)
	{
		sp_str = ft_calloc(2, sizeof(char *));
		if (!sp_str)
			return (NULL);
		sp_str[0] = ft_strdup(" ");
		sp_str[1] = NULL;
		return (sp_str);
	}
	sp_str = ft_calloc((ft_counter(s, c) + 1), sizeof(char *));
	if (sp_str && ft_allocate(s, c, sp_str) != 0)
		return (ft_assign(s, c, sp_str));
	return (NULL);
}
