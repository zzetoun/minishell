/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:51:08 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/14 16:25:06 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREEDOM_H
# define FREEDOM_H

void	free_ptr(void *ptr);
void	ft_close_fd(int fd[]);
//void	ft_free_fd(t_pipex *pipex);
void	ft_free_array(char **array);
//void	ft_freedom(t_pipex *pipex, int type);

#endif