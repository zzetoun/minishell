/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:07:31 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/13 14:39:07 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_error(int option, char **array, char *error)
{
	ft_free_array(array);
	ft_prnt_error(option, error);
}

void	ft_prnt_error(int option, char *error)
{
	if (option == 1)
		perror(error);
	else
		ft_printf(2, "%s\n", error);
	exit(EXIT_FAILURE);
}

