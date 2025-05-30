
//
// Created by IqMent on 10.05.2025.
//
#include "parser.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

static char	*extract_delim_0(const char *pos, bool *quoted, char *quote_char)
{
    const char	*p;
    size_t	len;
    char	*delim;

    p = pos + 2;
    while (*p && isspace((unsigned char)*p))
        p++;
    if (*p == '"' || *p == '\'')
    {
        *quoted = true;
        *quote_char = *p++;
    }
    else
        *quoted = false;

    {
        const char *start = p;
        while (*p && (*quoted ? *p != *quote_char : (!isspace((unsigned char)*p)
                                                     && *p != '<' && *p != '>' && *p != '|')))
            p++;
        len = p - start;
        delim = strndup(start, len);
    }
    return (delim);
}

static int	write_heredoc_block_1(int fd, const char *delim, bool quoted, t_data *data)
{
    char	*l;
    char	*out;

    for (;;)
    {
        l = readline("> ");
        if (!l || strcmp(l, delim) == 0)
        {
            free(l);
            break;
        }
        out = (quoted ? ft_strdup(l) : setup_env_in_line(l, data));
        if (!quoted)
            free(l);
        write(fd, out, strlen(out));
        write(fd, "\n", 1);
        write(fd, "\n", 1);
        free(out);
    }
    return (0);
}

static char	*replace_heredoc_with_tmpfile_2(char *line, const char *fname, char *pos, bool quoted, char quote_char)
{
    char	*after;
    size_t	pre_len;
    size_t	suf_len;
    char	*newl;

    pre_len = pos - line;
    after = pos + 2;
    while (*after && isspace((unsigned char)*after))
        after++;
    if (quoted)
    {
        after++;
        while (*after && *after != quote_char)
            after++;
        if (*after == quote_char)
            after++;
    }
    else
    {
        while (*after && !isspace((unsigned char)*after)
               && *after != '<' && *after != '>' && *after != '|')
            after++;
    }
    suf_len = strlen(after);
    newl = malloc(pre_len + 3 + strlen(fname) + (suf_len ? 1 + suf_len : 0) + 1);
    if (!newl)
        return (NULL);
    memcpy(newl, line, pre_len);
    memcpy(newl + pre_len, " < ", 3);
    memcpy(newl + pre_len + 3, fname, strlen(fname));
    if (suf_len)
    {
        newl[pre_len + 3 + strlen(fname)] = ' ';
        memcpy(newl + pre_len + 4 + strlen(fname), after, suf_len);
    }
    newl[pre_len + 3 + strlen(fname) + (suf_len ? 1 + suf_len : 0)] = '\0';
    return (newl);
}

static char	*handle_heredoc_3(char *line, int idx, t_data *data)
{
    char	*pos;
    char	*delim;
    char	quote_char;
    bool	quoted;
    char	fname[32];
    int	fd;

    pos = strstr(line, "<<");
    if (!pos)
        return (line);

    delim = extract_delim_0(pos, &quoted, &quote_char);
    snprintf(fname, sizeof(fname), "tmp_file_%d.tmp", idx);
    fd = open(fname, O_RDWR | O_CREAT | O_TRUNC, 0600);
    if (fd < 0)
    {
        perror("open heredoc");
        free(delim);
        return (line);
    }
    write_heredoc_block_1(fd, delim, quoted, data);
    close(fd);
    free(delim);
    return (replace_heredoc_with_tmpfile_2(line, fname, pos, quoted, quote_char));
}

char	*check_if_additional(char *line, t_data *data)
{
    int	idx;
    char *tmp;

    idx = 0;
    while (strstr(line, "<<"))
    {
        tmp = handle_heredoc_3(line, idx, data);
        if (tmp != line)
        {
            free(line);
            line = tmp;
        }
        idx++;
    }
    return (line);
}
