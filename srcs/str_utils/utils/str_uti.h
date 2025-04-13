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

/* ======== String Utilties ========== */

char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);

/* ======== String Join frees *s1 at exit ========== */
char	*ft_strjoin(char *s1, char const *s2);

char	**ft_split(const char *s, char c);

int		ft_strcmp(const char *s1, const char *s2);

size_t	ft_strlen(const char *s);

#endif