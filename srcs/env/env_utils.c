/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:22:52 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/25 03:46:34 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"

size_t ft_env_len(char **envp)
{
    size_t  size;
    
    size = 0;
    if (!envp || !*envp)
        return (0);
    while(envp[size])
        size++;
    return (size);
}


int ft_add_env(t_env_info *env, char *value)
{
    t_envp	*new_env;
    
    new_env = env->head;
	while (new_env)
        new_env = new_env->next;
    new_env = ft_calloc(1, sizeof(t_envp));
    if (!new_env)
        return (ft_free_env(env), 0);
    if (new_env->idx == 0)
        env->head = new_env;
    new_env->idx++;
    new_env->str = ft_strdup(value);
    new_env->next = NULL;
    if (env->tail != NULL)
        env->tail->next = new_env;
    env->tail = new_env;
    env->tail->next = NULL;
    env->size++;
    return (1);
}
