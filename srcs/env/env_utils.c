/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:22:52 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/21 19:53:24 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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


int ft_add_new_env(t_env_info *env, t_envp *envp, char *value)
{
    envp = ft_calloc(1, sizeof(t_envp));
    if (!envp)
        return (ft_free_env(env), 0);
    envp->idx++;
    envp->str = ft_strdup(value);
    envp->next = NULL;
    if (env->tail != NULL)
         env->tail->next = envp;
    env->tail = envp;
    env->size++;
    env->tail->next = NULL;
    return (1);
}
