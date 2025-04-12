/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 19:36:56 by zzetoun           #+#    #+#             */
/*   Updated: 2025/01/11 19:36:56 by zzetoun          ###   ########.ae       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdarg.h>
# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdint.h>
# include "ft_printf.h"
# include "get_next_line.h"
# include "str_uti.h"
# include "pipe_pars.h"
# include "pipe_uti.h"
# include "freedom.h"
# include "in_out.h"

# define EARGS "error: invalid arguments"
# define NOACC "error: permission denied"
# define EUNKN "error: unknown error"
# define PATHE "error: Commands Path"
# define ARGUE "error: Commands error"
# define ECFND 127
# define EPERM 126

#endif