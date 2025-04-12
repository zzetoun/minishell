/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:43:52 by zzetoun           #+#    #+#             */
/*   Updated: 2025/02/14 18:33:12 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IN_OUT_H
# define IN_OUT_H

void	pipe_infile(t_pipex *pipex, char **av);
void	pipe_outfile(t_pipex *pipex, char **av, int ac);
void	pipe_here_doc(t_pipex *pipex, char **av);
void	read_here_doc(t_pipex *pipex, char **av, int *fd);
char	*ft_strjoin_gnl(char *s1, char *s2);

#endif