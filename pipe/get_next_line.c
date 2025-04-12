/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:38:49 by zzetoun           #+#    #+#             */
/*   Updated: 2025/02/15 17:41:53 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strchr(char *str, char c)
{
	size_t	i;

	i = -1;
	if (!c)
		return ((char *)(str + ft_strlen(str)));
	while (++i < ft_strlen(str))
		if (str[i] == (char)c)
			return ((char *)(str + i));
	return (0);
}

char	*ft_remain(char *buff)
{
	char	*remain;
	int		idx;
	int		jdx;

	idx = 0;
	while (buff[idx] && buff[idx] != '\n')
		idx++;
	if (!buff[idx])
		return (free(buff), NULL);
	remain = malloc(ft_strlen(buff) - idx++);
	if (!remain)
		return (free(buff), NULL);
	jdx = 0;
	while (buff[idx])
		remain[jdx++] = buff[idx++];
	remain[jdx] = '\0';
	free(buff);
	return (remain);
}

char	*ft_line(char *buff)
{
	char	*line;
	int		len;

	if (!ft_strlen(buff))
		return (NULL);
	len = 0;
	while (buff[len] && buff[len] != '\n')
		len++;
	if (buff[len] == '\n')
		line = malloc(len + 2);
	else
		line = malloc(len + 1);
	if (!line)
		return (NULL);
	if (buff[len] == '\n')
		line[len + 1] = '\0';
	else
		line[len] = '\0';
	while (len >= 0)
	{
		line[len] = buff[len];
		len--;
	}
	return (line);
}

char	*ft_read_file(char *buff, int fd)
{
	char	*line;
	int		len;

	line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return (free(buff), NULL);
	len = 1;
	while (!ft_strchr(buff, '\n') && len != 0)
	{
		len = read(fd, line, BUFFER_SIZE);
		if (len < 0)
		{
			free(line);
			free(buff);
			buff = NULL;
			return (NULL);
		}
		line[len] = '\0';
		buff = ft_strjoin_gnl(buff, line);
	}
	free(line);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*print;

	if (fd < 0 || BUFFER_SIZE < 0 || BUFFER_SIZE > INT_MAX)
	{
		if (buff)
			free(buff);
		return (NULL);
	}
	buff = ft_read_file(buff, fd);
	if (!buff)
		return (NULL);
	print = ft_line(buff);
	if (!print)
	{
		free(buff);
		return (NULL);
	}
	buff = ft_remain(buff);
	return (print);
}
