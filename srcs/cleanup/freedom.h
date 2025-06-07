/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   freedom.h										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/30 15:51:08 by zzetoun		   #+#	#+#			 */
/*   Updated: 2025/04/16 19:26:40 by zzetoun		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef FREEDOM_H
# define FREEDOM_H
#include "../../include/minishell.h"

void	ft_free_io(t_io_fds *io);
void	ft_free_dptr(void *pointer);
void 	ft_free_dptr(void **pointer);
void	ft_free_array(char **array);
void	exit_full(t_data *data, int exit_num);
void	ft_freedom(t_data **data, bool clear_history);
void	ft_close_fds(t_command *cmds, bool close_backups);

#endif
