/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:23:23 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/04 19:43:41 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

void	ignore_sigquit(void);
void	set_signals_heredoc(void);
void	set_signals_interactive(void);
void	signal_reset_prompt(int signo);
void	signal_print_newline(int signal);
void	set_signals_noninteractive(void);
void	signal_heredoc_interrupt(int signo);

#endif
