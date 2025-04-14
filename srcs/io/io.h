/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:10:19 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/14 16:45:24 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

int	restore_io(t_io_fds *io);
int	redirect_io(t_io_fds *io);
int	check_infile_outfile(t_io_fds *io);


#endif