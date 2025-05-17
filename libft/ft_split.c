/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imickhai <imickhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:24:51 by imickhai          #+#    #+#             */
/*   Updated: 2024/12/23 16:57:02 by imickhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int		count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	**get_sizes(char const *s, char c, int *j)
{
	int		count;
	char	**result;

	*j = 0;
	count = count_words(s, c);
	if (count == 0)
	{
		result = (char **)malloc(1 * sizeof(char *));
		if (!result)
			return (NULL);
		result[0] = NULL;
		return (result);
	}
	result = (char **)malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[count] = NULL;
	return (result);
}

static void	count_len(char const *s, char c, int *len)
{
	*len = 0;
	while (s[*len] && s[*len] != c)
		(*len)++;
}

static char	**make_strings(char const *s, char c)
{
	char	**result;
	int		i;
	int		j;
	int		len;

	result = get_sizes(s, c, &j);
	if (!result)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		count_len(s, c, &len);
		result[j] = malloc((len + 1) * sizeof(char));
		if (!result[j])
			return (NULL);
		i = 0;
		while (i < len)
			result[j][i++] = *s++;
		result[j++][i] = '\0';
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	if (!s)
		return (NULL);
	return (make_strings(s, c));
}

// static char	**make_strings(char const *s, char c)
// {
// 	char	**result;
// 	int		i;
// 	int		j;
// 	int		len;

// 	result = get_sizes(s, c);
// 	if (!result)
// 		return NULL;
// 	j = 0;
// 	while (*s)
// 	{
// 		while (*s == c)
// 			s++;
// 		if (!*s)
// 			break;
// 		len = 0;
// 		while (s[len] && s[len] != c)
// 			len++;
// 		result[j] = malloc((len + 1) * sizeof(char));
// 		if (!result[j]) return NULL;
// 		i = 0;
// 		while (i < len)
// 			result[j][i++] = *s++;
// 		result[j++][i] = '\0';
// 	}
// 	return result;
// }

// static int count_words(const char *s, char c)
// {
//     int count = 0;
//     while (*s)
//     {
//         while (*s == c)
//             s++;
//         if (*s != '\0')
//         {
//             count++;
//             while (*s && *s != c)
//                 s++;
//         }
//     }
//     return count;
// }
// static char	**get_sizes(char const *s, char c)
// {
// 	int		count;
// 	char	**result;
// 	count = count_words(s, c);
// 	if (count == 0)
// 	{
// 		result = (char **)malloc(1 * sizeof(char *));
//         if (!result)
//             return (NULL);
//         result[0] = NULL;
//         return result;
// 	}
// 	result = (char**)malloc((count + 1) * sizeof(char*));
// 	if(!result)
// 		return (NULL);
// 	result[count] = NULL;
// 	return (result);
// }
// static char	**make_strings(char const *s, char c)
// {
// 	char	**result;
// 	int		i;
// 	int		j;
// 	int		len;
// 	result = get_sizes(s, c);
// 	if (!result)
// 		return (0);
// 	j = 0;
// 	while (*s)
// 	{
// 		while (*s == c)
// 			s++;
// 		if (*s == '\0')
// 			break;
// 		len = 0;
// 		while (s[len] && s[len] != c)
// 			len++;
// 		result[j] = (char *)malloc((len + 1) * sizeof(char));
// 		if (!result[j])
// 			return (0);
// 		i = 0;
// 		while (i < len)
// 			result[j][i++] = *s++;
// 		result[j][i] = '\0';
// 		j++;
// 	}
// 	return (result);
// } 
// char	**ft_split(char const *s, char c)
// {
// 	if (!s)
//         return NULL;
// 	return make_strings(s, c);	
// }
// static size_t	ft_count(const char *s, char c)
// {
// 	size_t	count;
// 	count = 0;
// 	while (*s)
// 	{
// 		if (*s != c)
// 		{
// 			++count;
// 			while (*s && *s != c)
// 				++s;
// 		}
// 		else
// 			++s;
// 	}
// 	return (count);
// }
// char	**ft_split(const char *s, char c)
// {
// 	char	**split;
// 	size_t	i;
// 	size_t	len;
// 	if (!s)
// 		return (0);
// 	i = 0;
// 	split = ft_calloc(ft_count(s, c) + 1, sizeof(char *));
// 	if (split == NULL)
// 		return (0);
// 	while (*s)
// 	{
// 		if (*s != c)
// 		{
// 			len = 0;
// 			while (*s && *s != c && ++len)
// 				++s;
// 			split[i++] = ft_substr(s - len, 0, len);
// 		}
// 		else
// 			++s;
// 	}
// 	split[i] = 0;
// 	return (split);
// }
