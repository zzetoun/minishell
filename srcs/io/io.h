/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:23:42 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/23 16:52:39 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

int	restore_io(t_io_fds *io);
int	redirect_io(t_io_fds *io);
int	create_pipes(t_data *data);
int	check_infile_outfile(t_io_fds *io);
int	set_pipe_fds(t_command *cmds, t_command *c);

void	close_pipe_fds(t_command *cmds, t_command *skip_cmd);

#endif
