/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imickhai <imickhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:39:07 by imickhai          #+#    #+#             */
/*   Updated: 2024/12/23 15:48:39 by imickhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*result;
	t_list		*tmp;
	t_list		*new_lst;

	result = NULL;
	tmp = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		new_lst = ft_lstnew(f(lst->content));
		if (!new_lst)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		if (!result)
			result = new_lst;
		else
			tmp->next = new_lst;
		tmp = new_lst;
		lst = lst->next;
	}
	return (result);
}
