/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:23:54 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/07 18:23:54 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLLERS_H
# define CONTROLLERS_H

/* ============ ERROR & EXIT HANDLING ============ */
void	ft_free_fd(t_command *cmd);
void	ft_prnt_error(int option, char *error);
void	errmsg(char *error, char *detail, int quotes);
void	exit_error(int option, char **array, char *error);

int		errmsg_cmd(char *cmd, char *detail, char *error, int err_nb);

#endif
