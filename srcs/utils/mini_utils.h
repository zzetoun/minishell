/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:22:57 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/07 18:22:57 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_UTILS_H
# define MINI_UTILS_H

void	setup_io(t_command *cmd);
int		setup_mini(t_data *data, char **envp);
void	linked_list_print(t_env_info *env, char **_envp, int option);

#endif 
