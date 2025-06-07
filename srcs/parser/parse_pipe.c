/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:39:13 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 21:39:15 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


bool	setup_io(t_command *cmd);
void	linked_list_print(t_env_info *env, char **_envp, int option);

	last_cmd = get_last_cmd(*cmd);
	last_cmd->pipe_output = true;
	add_back_cmd(&last_cmd, add_new_cmd());
	*token_lst = (*token_lst)->next;
}
