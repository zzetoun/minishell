/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_list_prnt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:46:55 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/08 13:52:31 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	linked_list_print(t_env_info *env, char **_envp, int option)
{
	t_envp *envp;
	int	idx;

	envp = env->head;
	idx = 0;
	ft_printf(1, "env size: {%d}\n", env->size);
	ft_printf(1, "env shlvl: {%d}\n", env->shlvl);
	while (envp)
	{
		if (option == 2 && _envp)
		{
			ft_printf(1, "[%d] envp->key: {%s}\n envp->value: {%s}\n envp->str: {%s}\n",envp->idx, envp->key, envp->value, envp->str);
			ft_printf(1, "[%d] _envp: {%s}\n", idx, _envp[idx]);
		}
		else if (option == 1)
			ft_printf(1, "[%d] envp->key: {%s}\n envp->value: {%s}\n envp->str: {%s}\n",envp->idx, envp->key, envp->value, envp->str);
		else if (option == 0)
			ft_printf(1, "[%d] _envp: {%s}\n", idx, _envp[idx]);
		else
			break ;
		idx++;
		envp = envp->next;
	}
	printf("last envp %p\n", envp);
}
