/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:59:14 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/24 16:36:00 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static char	*copy_until_quote(char *line, size_t *i, char quote)
// {
//     size_t	start;

// 	start = *i;
//     (*i)++;
//     while (line[*i] && line[*i] != quote)
//         (*i)++;
//     if (line[*i] == quote)
//         (*i)++;
//     return (ft_substr(line, start, *i - start));
// }

// static char	*copy_until_space(char *line, size_t *i)
// {
//     size_t start;
	
// 	start = *i;
//     while (line[*i] && line[*i] != ' ' && line[*i] != '\'' && line[*i] != '\"')
//         (*i)++;
// 		return (ft_substr(line, start, *i - start));
// }

// char **minishell_split(char *input)
// {
//     char *line = setup_env_in_line(input);
//     char **result = NULL;
//     size_t count = 0;
//     size_t i = 0;

//     while (line[i])
//     {
//         while (line[i] == ' ')
//             i++;
//         if (line[i] == '\0')
//             break;
//         char *part = NULL;
//         if (line[i] == '\'' || line[i] == '\"')
//             part = copy_until_quote(line, &i, line[i]);
//         else
//             part = copy_until_space(line, &i);

//         if (part)
//         {
//             char **new_result = realloc(result, sizeof(char *) * (count + 2));
//             if (!new_result)
//             {
//                 free(part);
//                 break;
//             }
//             result = new_result;
//             result[count++] = part;
//             result[count] = NULL;
//         }
//     }
//     return result;
// }

bool	cmd_args_split(t_command *cmd, char *input)
{
	char	*args;
	int	 idx;

	args = ft_strchr(input, ' ');
	ft_printf(1, "args: {%s}\n", args);
	cmd->command = ft_substr(input, 0, ft_strlen(input) - ft_strlen(args));
	ft_printf(1, "cmd: {%s}\n", cmd->command);
	cmd->args = ft_split(args, ' ');
	idx = -1;
	while (cmd->args && cmd->args[++idx])
		ft_printf(1, "arg[%d]= {%s}\n", idx, cmd->args[idx]);
	return (true);
}
