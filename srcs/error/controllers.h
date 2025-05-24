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
bool	how_to_message(bool return_val);
int		errmsg(char *cmd, char *detail, char *error, int err_nb);

#endif
