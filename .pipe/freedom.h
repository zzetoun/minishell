/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:51:08 by zzetoun           #+#    #+#             */
/*   Updated: 2025/02/14 18:05:52 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREEDOM_H
# define FREEDOM_H

# include "pipex.h"

void	ft_close_fd(int fd[]);
void	ft_free_fd(t_pipex *pipex);
void	ft_free_array(char **array, int n);
void	ft_free_2d_array(char ***array, int n);
void	ft_freedom(t_pipex *pipex, int type);

#endif