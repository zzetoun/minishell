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
    char    *tmp;
    int     idx;
    
    while(args && *args)
    {
        tmp = *args;
        idx = 0;
        if (!tmp || (!ft_isalpha(tmp[idx]) && tmp[idx] != '_'))
        {
            ft_printf(2, "-Minishell: export: `%s':%s\n", *args, MINIEXP);
            return (0);
        }
        while(tmp[++idx])
        {
            if (tmp[idx] == '=')
                break;
            else if (!ft_isalnum(tmp[idx]) && tmp[idx] != '_')
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
        idx = -1;
        while(tmp[++idx])
        {
            if (tmp[idx] == '=')
            {
                set_env(env, , ft_strchr(tmp, '=') + 1);
                break;
            }
            else if (!ft_isalnum(tmp[idx]) && tmp[idx] != '_')
                ft_printf(2, "-Minishell: export: `%s':%s\n", *args, MINIEXP);
        }
        args++;
    }
    return (1);   
}

int ft_export(t_env_info *env, char **args)
{
    char    **envp;

    envp = ft_env_to_str(env);
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
