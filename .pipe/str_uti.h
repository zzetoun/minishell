/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_uti.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 19:34:42 by zzetoun           #+#    #+#             */
/*   Updated: 2025/01/11 19:34:42 by zzetoun          ###   ########.ae       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_UTI_H
# define STR_UTI_H

int		ft_strncmp(const char *s1, const char *s2, size_t n);

size_t	ft_strlen(const char *s);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char *s, char c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

void	*ft_calloc(size_t counter, size_t size);

#endif