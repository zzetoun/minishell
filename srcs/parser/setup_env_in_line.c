//
// Created by IqMent on 09.05.2025.
//
#include "parser.h"

//static char *ft_strjoin_free_1(char *s1, const char *s2)
//{
//    char *res;
//
//    res = ft_strjoin(s1, s2);
//    free(s1);
//    return res;
//}

size_t handle_single_quotes(char *line, size_t i, char **result)
{
    size_t start;
	char 	*sub_str;

    start = ++i;
    while (line[i] && line[i] != '\'') {
		i++;
	}
	sub_str = ft_substr(line, start, i - start);
	if (!sub_str)
		sub_str = ft_strdup("");
    *result = ft_strjoin_free(*result,
              sub_str);
	ft_free_ptr(sub_str);
    return (i);
}

size_t handle_env_variable(char *line, size_t i, char **result, t_data *data)
{
    size_t j;

    j = i + 1;
    while (line[j] && (ft_isalnum(line[j]) || line[j] == '_'))
        j++;
    char *env_var = ft_strndup(line + i + 1, j - i - 1);
    char *env_val = get_env(data->env, env_var);
    if (!env_val)
    {
        env_val = ft_strdup("\n");
    }
    if (env_val)
        *result = ft_strjoin_free(*result, env_val);
    ft_free_ptr(env_var);
    return j - 1;
}

void append_char(char **result, const char c)
{
    char str[2] = {c, '\0'};
    *result = ft_strjoin_free(*result, str);
}

char *setup_env_in_line(char *line, t_data *data)
{
    char *result = ft_strdup("");
    size_t i = (size_t)-1;
    int in_double_quotes = 0;

    while (line[++i])
    {
        if (line[i] == '"')
        {
            in_double_quotes = !in_double_quotes;
            append_char(&result, '"');
        }
        else if (line[i] == '\'' && !in_double_quotes)
            i = handle_single_quotes(line, i, &result);
        else if (line[i] == '$' && line[i + 1] == '?' &&
                 (in_double_quotes || (!in_double_quotes &&
                                       line[i + 2] != '"' && line[i + 2] != '\'')))
        {
            append_char(&result, '$');
            append_char(&result, '?');
            i++;
        }
        else if (line[i] == '$' && (in_double_quotes || (!in_double_quotes &&
                                                         line[i + 1] != '"' && line[i + 1] != '\'')))
        {

            i = handle_env_variable(line, i, &result,data);
        }
        else
            append_char(&result, line[i]);
    }
    return result;
}
