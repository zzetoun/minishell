/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:22:52 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/27 00:45:27 by zzetoun          ###   ########.fr       */
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

char    **ft_env_to_str(t_env_info *env)
{
    t_envp  *envp;
    char    **str;

    envp = env->head;
    str = ft_calloc(env->size, sizeof(char *));
    if (!str)
        return (0);
    while(envp)
    {
        if (envp->idx < env->size - 1)
        {
            str[envp->idx] = ft_strdup(envp->str);
            if (!str[envp->idx])
                return (ft_free_array(str), NULL);   
        }
        envp = envp->next;
    }
    return (str);
}