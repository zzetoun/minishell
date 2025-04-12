/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_pars.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:37:26 by zzetoun           #+#    #+#             */
/*   Updated: 2025/01/27 13:37:26 by zzetoun          ###   ########.ae       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_PARS_H
# define PIPE_PARS_H

# include "s_pipex.h"

int		ft_error(char *error);
int		ft_parse(t_pipex *pipex, int ac, char **av);
int		parse_cmd_paths(t_pipex *pipex, int ac, char **av, char **envp);
int		parse_cmd_args(t_pipex *pipex, int ac, char **av);

#endif