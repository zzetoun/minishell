/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:10:12 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/01 17:19:17 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"

static int  export_args_check(char **args)
{
    char    *ar;
    int     idx;
    
    while(args && *args)
    {
        ar = *args;
        if (!ar || (!ft_isalpha(ar[0]) && ar[0] != '_' && !ft_isspace(ar[0])))
        {
            ft_printf(2, "-Minishell: export: `%s':%s\n", *args, MINIEXP);
            return (0);
        }
        idx = 0;
        while(ar[++idx])
        {
            if (ar[idx] == '=')
                break;
            else if (!ft_isalnum(ar[idx]) && ar[idx] != '_')
            {
                ft_printf(2, "-Minishell: export: `%s':%s\n", *args, MINIEXP);
                return (0);
            }
        }
        args++;
    }
    return (1);
}

static int export_print(char **envp, size_t size)
{
    size_t  idx;
    size_t  jdx;
    char    *tmp;

    idx = -1;
    tmp = NULL;
    while (++idx < size)
    {
        jdx = idx;
        while (++jdx < size)
        {
            if (ft_strncmp(envp[idx], envp[jdx], -1) > 0)
            {
                tmp = envp[idx];
                envp[idx]  = envp[jdx];
                envp[jdx]  = tmp;
            }
        }
    }
    idx = -1;
    while(envp[++idx])
        ft_printf(1, "declare -x %s\n", envp[idx]);
    ft_free_array(envp);
    return (1);
}

static int  ft_args_pars(t_env_info *env, char **args)
{
    char    *tmp;
    int     idx;
    
    while(args && *args)
    {
        tmp = *args;
        idx = 0;
        while (tmp && ft_isspace(tmp[idx]))
            idx++;
        tmp += idx;
        if (tmp && ft_strlen(tmp) > 1 && *tmp != '=')
            set_env(env, tmp, NULL);
        args++;
    }
    return (1);
}

int ft_export(t_env_info *env, char **args)
{
    char    **envp;

    envp = ft_env_to_export(env->head, env->size);
    if (!envp)
    {
        ft_printf(2, "-Minishell: export: enviromets are NULL\n");
        return (0);
    }
    if (args && !export_args_check(args))
        return (0);
    else if (!args)
        return (export_print(envp, env->size));
    else
        return (ft_args_pars(env, args));
    return (0);
}

char *ft_str_quot_free(char *s)
{
    size_t  len;
    size_t  idx;
    char    *str;

    if (!s)
        return (NULL);
    len = ft_strlen(s);
    idx = -1;
    while(s[++idx])
        if (s[idx] == '\'' || s[idx] == '\"')
            len--;
    str = ft_calloc(len + 1, sizeof(char));
    if (!str)
        return (NULL);
    idx = -1;
    len = 0;
    while(s[++idx])
        if(s[idx] != '\'' && s[idx] != '\"')
            str[len++] = s[idx];
    str[len] = '\0';
    free(s);
    return (str);
}
