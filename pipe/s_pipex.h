/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_pipex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:03:39 by zzetoun           #+#    #+#             */
/*   Updated: 2025/02/12 14:59:00 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_PIPEX_H
# define S_PIPEX_H

typedef struct s_pipex
{
	int		infd;
	int		outfd;
	int		here_doc;
	int		in_invalid;
	int		out_invalid;
	char	**cmd_paths;
	char	***cmd_args;
	int		cmd_num;
	int		status;
	pid_t	pid;
}	t_pipex;

#endif