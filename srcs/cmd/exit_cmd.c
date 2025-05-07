/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:49:06 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/06 23:11:49 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static int	get_exit_code(char *arg, int	*error)
// {
// 	unsigned long long	i;

// 	if (!arg)
// 		return (final_exit_code);
// 	i = 0;
// 	while (ft_isspace(arg[i]))
// 		i++;
//	 if (arg[i] == '\0')
//		 *error = 1;
// 	i += (arg[i] == '-' || arg[i] == '+');
//	 if (!ft_isdigit(arg[i]))
//		 *error = 1;
// 	while (arg[i])
// 	{
// 		if (!ft_isdigit(arg[i]) && !ft_isspace(arg[i]))
// 			*error = 1;
// 		i++;
// 	}
// 	i = ft_atoi(arg, error);
// 	return (i % 256);
// }
