/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imickhai <imickhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:36:03 by imickhai          #+#    #+#             */
/*   Updated: 2024/12/23 15:46:02 by imickhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	count(int n)
{
	int		i;

	if (n == 0)
		return (1);
	i = 0;
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned int	size;
	char			*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	size = count(n);
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	str[size] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n != 0)
	{
		str[--size] = ('0' + (n % 10));
		n = n / 10;
	}
	return (str);
}

// int main() { //-5859 //-2147483648
//     int num = -2147483648;
//     char *result = ft_itoa(num);
//     printf("%s\n", result);
//     free(result);
//     return 0;
// }
