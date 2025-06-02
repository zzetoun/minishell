//
// Created by iqment on 6/1/25.
//

#include "../parser/parser.h"

bool	has_quotes(const char *str)
{
    if (!str)
        return (false);
    while (*str)
    {
        if (*str == '\'' || *str == '"')
            return (true);
        str++;
    }
    return (false);
}

bool	has_unclosed_quotes(const char *line)
{
    char state = 0;
    size_t i = 0;

    while (line[i])
    {
        if (state == 0 && (line[i] == '"' || line[i] == '\''))
            state = line[i];
        else if (state == line[i])
            state = 0;
        i++;
    }
    return (state != 0);
}

char	*ft_replace_substr(const char *str, const char *target, const char *replacement)
{
	size_t str_len;
	size_t target_len;
	size_t repl_len;
	size_t count;
	size_t new_len;
	char *result;
	const char *tmp;
	const char *src;
	char *dst;

	if (!str || !target || !replacement)
		return NULL;
	str_len = ft_strlen(str);
	target_len = ft_strlen(target);
	repl_len = ft_strlen(replacement); //Initing variables <><><>
	count = 0;
	tmp = str;
	while ((tmp = strstr(tmp, target)))
	{
		count++;
		tmp += target_len;
	}\
	if (count == 0)
		return (ft_strdup(str));
	new_len = str_len - (count * target_len) + (count * repl_len);
	result = malloc(new_len + 1);
	if (!result)
		return NULL;
	src = str;
	dst = result;
	while (*src)
	{
		if (strncmp(src, target, target_len) == 0)
		{
			memcpy(dst, replacement, repl_len);
			dst += repl_len;
			src += target_len;
		}
		else
			*dst++ = *src++;
	}
	*dst = '\0';
	return (result);
}