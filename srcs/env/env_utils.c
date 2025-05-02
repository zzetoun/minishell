/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:22:52 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/29 20:38:32 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"

size_t ft_darray_len(char **str)
{
    size_t  size;
    
    size = 0;
    if (!str || !*str)
        return (0);
    while(str[size])
        size++;
    return (size);
}

int ft_key_cmp(const char *str, const char *key)
{
    if (!str || !key)
        return (1);
    while(*str && *str != '=' && *key && *key != '=')
    {
        if (*str == *key)
        {
            str++;
            key++;
        }
        else
            break;
    }
    if ((!*key || *key == '=') && (!*str || *str == '='))
        return (0);
    return (1);
}

char    **ft_env_to_str(t_env_info *env)
{
    t_envp  *envp;
    char    **str;

    envp = env->head;
    str = ft_calloc(env->size + 1, sizeof(char *));
    if (!str)
        return (0);
    while(envp)
    {
        str[envp->idx] = ft_strdup(envp->str);
        if (!str[envp->idx])
            return (ft_free_array(str), NULL);
        envp = envp->next;
    }
    return (str);
}

char    **ft_env_to_export(t_env_info *env)
{
    t_envp  *envp;
    char    **str;
    size_t  idx;
    size_t  len;

    envp = env->head;
    str = ft_calloc(env->size + 1, sizeof(char *));
    if (!str)
        return (0);
    while(envp)
    {
        idx = envp->idx;
        len = ft_strlen(envp->str) - ft_strlen(ft_strchr(envp->str, '='));
        str[idx] = ft_substr(envp->str, 0, len);
        str[idx] = ft_strjoin_free(str[idx], "=\"");
        str[idx] = ft_strjoin_free(str[idx], ft_strchr(envp->str, '=') + 1);
        str[idx] = ft_strjoin_free(str[idx], "\"");
        if (!str[envp->idx])
            return (ft_free_array(str), NULL);
        envp = envp->next;
    }
    return (str);
}

int ft_add_new_env(t_env_info *env, char *key, char *value)
{
    t_envp	*new_env;
    
    if (env->size != 0)
    {
        new_env = env->head;
        while (new_env->next)
            new_env = new_env->next;
    }
    new_env = ft_calloc(1, sizeof(t_envp));
    if (!new_env)
        return (ft_free_env(env), 0);
    if (env->size == 0)
        env->head = new_env;
    new_env->idx = env->size;
    if (key || value)
        new_env->str = ft_strjoin(key, value);
    new_env->next = NULL;
    if (env->tail != NULL)
        env->tail->next = new_env;
    env->tail = new_env;
    env->size++;
    return (1);
}
