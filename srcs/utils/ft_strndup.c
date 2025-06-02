//
// Created by IqMent on 09.05.2025.
//
#include "../parser/parser.h"
#include <string.h>

char *ft_strndup(const char *str, size_t n)
{
    char *dup;
    size_t len;

    if (!str)
        return (NULL);
    len = ft_strlen(str);
    if (len > n)
        len = n;
    dup = malloc(len + 1);
    if (!dup)
        return (NULL);
    strlcpy(dup, str, len + 1);
    return (dup);
}
