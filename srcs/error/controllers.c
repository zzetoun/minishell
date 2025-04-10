/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imickhai <imickhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:07:31 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/10 16:03:18 by imickhai         ###   ########.fr       */
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
		printf("%s\n", error);
	exit(EXIT_FAILURE);
}

