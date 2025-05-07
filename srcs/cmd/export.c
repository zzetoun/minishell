/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:49:15 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/06 22:49:15 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	set_export(t_env_info *env, char *arg)
{
	char	*s;

	if (ft_strlen(ft_strchr(arg, '=')) >= 1)
	{
		s = ft_substr(arg, 0, ft_strlen(arg) - ft_strlen(ft_strchr(arg, '=')));
		if (ft_strlen(ft_strchr(arg, '=')) == 1)
			set_env(env, s, NULL);
		else
			set_env(env, s, ft_strchr(arg, '=') + 1);
		free(s);
		return (1);
	}
	else if (!env_key(env, arg))
		ft_add_new_env(env, arg, NULL);
	return (0);
}

static char	**ft_env_to_export(t_envp *en, size_t size)
{
	char	**s;

	s = ft_calloc(size + 1, sizeof(char *));
	if (!s)
		return (0);
	while (en)
	{
		if (ft_strchr(en->str, '='))
		{
			s[en->idx] = ft_strjoin(en->key, "=\"");
			s[en->idx] = ft_strjoin_free(s[en->idx], en->value);
			s[en->idx] = ft_strjoin_free(s[en->idx], "\"");
		}
		else
			s[en->idx] = ft_strdup(en->key);
		en = en->next;
	}
	return (s);
}

int	export_args_check(char *arg, char *cmd)
{
	int	i;

	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_' && !ft_isspace(arg[0])))
	{
		ft_printf(2, "-Minishell: %s: `%s':%s\n", cmd, arg, MINIERID);
		return (1);
	}
	else if (str_compare(cmd, "unset") && ft_strchr(arg, '='))
	{
		ft_printf(2, "-Minishell: %s: `%s':%s\n", cmd, arg, MINIERID);
		return (1);
	}
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '=' && str_compare(cmd, "export"))
			break ;
		else if (!ft_isalnum(arg[i]) && arg[i] != '_' && ft_isspace(arg[i]))
		{
			ft_printf(2, "-Minishell: %s: `%s':%s\n", cmd, arg, MINIERID);
			return (1);
		}
	}
	return (0);
}

static int	export_print(char **envp, size_t size)
{
	size_t	idx;
	size_t	jdx;
	char	*tmp;

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
				envp[idx] = envp[jdx];
				envp[jdx] = tmp;
			}
		}
	}
	idx = -1;
	while (envp[++idx])
		ft_printf(1, "declare -x %s\n", envp[idx]);
	ft_free_array(envp);
	return (1);
}

int	ft_export(t_env_info *env, char **args)
{
	char	**envp;
	char	*arg;
	int		error;

	envp = ft_env_to_export(env->head, env->size);
	error = 0;
	if (!envp)
	{
		ft_printf(2, "-Minishell: export: enviromets are NULL\n");
		return (error);
	}
	if (!args || !*args)
		export_print(envp, env->size);
	while (args && *args)
	{
		arg = *args;
		error = export_args_check(arg, "export");
		if (error )
			set_export(env, arg);
		args++;
	}
	return (error);
}
