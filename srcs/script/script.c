#include "../include/minishell.h"
#include "script.h"

static char **read_file_lines(const char *path)
{
    int fd;
    char buffer[1025];
    ssize_t bytes;
    char *content;
    char *tmp;

    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (NULL);
    content = ft_strdup("");
    if (!content)
    {
        close(fd);
        return (NULL);
    }
    while ((bytes = read(fd, buffer, 1024)) > 0)
    {
        buffer[bytes] = '\0';
        tmp = ft_strjoin_free(content, buffer);
        if (!tmp)
        {
            free(content);
            close(fd);
            return (NULL);
        }
        content = tmp;
    }
    close(fd);
    if (bytes == -1)
    {
        free(content);
        return (NULL);
    }
    tmp = content;
    content = ft_strtrim(content, "\r");
    free(tmp);
    char **lines = ft_split(content, '\n');
    free(content);
    return (lines);
}

void    minishell_script(t_data *data, char *path)
{
    char    **lines;
    int     i;

    data->interactive = false;
    lines = read_file_lines(path);
    if (!lines)
        exit_full(data, errmsg("open", path, strerror(errno), errno));
    i = -1;
    while (lines[++i])
    {
        data->user_input = ft_strdup(lines[i]);
        if (cmd_args_split(data, data->user_input))
            g_final_exit_code = execute(data);
        else
            g_final_exit_code = 1;
        ft_freedom(data, false);
    }
    ft_free_array(lines);
}
