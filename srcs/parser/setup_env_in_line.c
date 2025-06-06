

#include "parser.h"

size_t handle_single_quotes(char *line, size_t i, char **result)
{
    size_t	start;
	char 	*sub_str;

    start = ++i;
    while (line[i] && line[i] != '\'')
		i++;
	sub_str = ft_substr(line, start, i - start);
	if (!sub_str)
		sub_str = ft_strdup("");
    *result = ft_strjoin_free(*result,sub_str);
	ft_free_ptr(sub_str);
    return (i);
}

size_t handle_env_variable(char *line, size_t i, char **result, t_data *data)
{
    size_t j;
	char *env_var;
	char *env_val;

    j = i + 1;
    while (line[j] && (ft_isalnum(line[j]) || line[j] == '_'))
        j++;
    env_var = ft_strndup(line + i + 1, j - i - 1);
    env_val = get_env(data->env, env_var);
    if (!env_val)
        env_val = ft_strdup("\n");
    if (env_val)
        *result = ft_strjoin_free(*result, env_val);
    ft_free_ptr(env_var);
    return j - 1;
}

void append_char(char **result, const char c)
{
    *result = ft_strjoin_free(*result,&c);
}

char *setup_env_in_line(char *line, t_data *data)
{
    char	*result;
	size_t	i;
	int		in_double_quotes;

	result = ft_strdup("");
	i = (size_t)-1;
    in_double_quotes = 0;
    while (line[++i])
    {
        if (line[i] == '"')
        {
            in_double_quotes = !in_double_quotes;
            append_char(&result, '"');
        }
        else if (line[i] == '\'' && !in_double_quotes)
            i = handle_single_quotes(line, i, &result);
        else if (line[i] == '$' && line[i + 1] == '?')
        {
            append_char(&result, '$');
            append_char(&result, '?');
            i++;
        }
        else if (line[i] == '$' && (line[i + 1] != '"' && line[i + 1] != '\''))
            i = handle_env_variable(line, i, &result,data);
        else
            append_char(&result, line[i]);
    }
    return result;
}

//char	*setup_env_in_line(char *input, t_data *data)
//{
//	int		i;
//	int		j;
//	int		len;
//	char	*result;
//
//	if (!input)
//		return (NULL);
//	len = ft_strlen(input);
//	result = malloc(len + 1);
//	if (!result)
//		return (NULL);
//	i = 0;
//	j = 0;
//	while (i < len)
//	{
//		if (input[i] == '$')
//		{
//			int	var_start = i + 1;
//			int	var_len = 0;
//			/* Count variable name length with boundary check */
//			while ((var_start + var_len) < len &&
//				   (ft_isalnum(input[var_start + var_len]) || input[var_start + var_len] == '_'))
//				var_len++;
//			/* If a variable name exists, expand it */
//			if (var_len > 0)
//			{
//				char	*var_key = ft_strndup(input + var_start, var_len);
//				char	*env_val = get_env(data->env, var_key);
//				ft_free_ptr(var_key);
//				if (env_val)
//				{
//					int	k = 0;
//					while (env_val[k])
//						result[j++] = env_val[k++];
//				}
//				i = var_start + var_len;
//				continue ;
//			}
//		}
//		result[j++] = input[i++];
//	}
//	result[j] = '\0';
//	return (result);
//}