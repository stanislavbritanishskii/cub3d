/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 01:42:15 by sbritani          #+#    #+#             */
/*   Updated: 2022/10/24 02:00:46 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*rec(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;

	if (!lst)
		return (NULL);
	res = malloc(sizeof(t_list));
	if (!res)
		return (NULL);
	res->content = f(lst->content);
	res->next = rec(lst->next, f, del);
	return (res);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;

	res = rec(lst, f, del);
	if (!res)
		return (NULL);
	if (ft_lstsize(res) != ft_lstsize(lst))
	{	
		ft_lstclear(&res, del);
		return (NULL);
	}
	return (res);
}
