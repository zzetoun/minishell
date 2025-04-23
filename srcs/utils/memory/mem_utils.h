/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 22:00:00 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/09 15:08:31 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_UTILS_H
# define MEM_UTILS_H

void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t counter, size_t size);
void	*ft_memmove(void *dst, const void *src, size_t len);

#endif