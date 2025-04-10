/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:14:49 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/09 16:03:09 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	move_buffer(char *buffer)
{
	if (ft_strchr(buffer, '\n'))
		ft_memmove(buffer, (ft_strchr(buffer, '\n') + 1),
			ft_strlen(ft_strchr(buffer, '\n') + 1) + 1);
	else
		buffer[0] = 0;
}

static char	*join_buf(char *result, char *buffer)
{
	char	*line;

	if (result == NULL)
	{
		result = ft_calloc(1, sizeof(char));
		if (result == NULL)
			return (NULL);
	}
	line = ft_strjoin_gl(result, buffer);
	if (line == NULL)
	{
		free(result);
		return (NULL);
	}
	free(result);
	move_buffer(buffer);
	return (line);
}

char	*ft_strjoin_gl(char *result, char *buffer)
{
	char	*new;
	size_t	i;
	int		j;

	i = 0;
	j = -1;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] && buffer[i] == '\n')
		i++;
	new = malloc((sizeof(char) * ft_strlen(result) + i) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (result[++j])
		new[j] = result[j];
	while (buffer[i] && buffer[i] != '\n')
		new[j++] = buffer[i++];
	if (buffer[i] && buffer[i] == '\n')
		new[j++] = buffer[i++];
	new[j] = '\0';
	return (new);
}

char	*get_next_line(int fd)
{
	static char	buffer[OPEN_MAX][BUFFER_SIZE + 1u];
	char		*ret;
	ssize_t		bytes;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE > INT_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	ret = NULL;
	while (ret == NULL || !ft_strchr(ret, '\n'))
	{
		if (!*buffer[fd])
		{
			bytes = read(fd, buffer[fd], BUFFER_SIZE);
			if (bytes == 0)
				return (ret);
			if (bytes < 0 && ret)
				free(ret);
			if (bytes < 0)
				return (NULL);
			buffer[fd][bytes] = '\0';
		}
		ret = join_buf(ret, buffer[fd]);
		if (ret == NULL)
			return (NULL);
	}
	return (ret);
}
