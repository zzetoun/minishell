/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 19:34:42 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/27 17:07:32 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef STR_UTI_H
# define STR_UTI_H

/* ======== String Utilties ========== */

char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin_free(char *s1, char const *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	**ft_split(const char *s, char c);

int     ft_strncmp(const char *s1, const char *s2, size_t n);

size_t	ft_strlen(const char *s);

#endif