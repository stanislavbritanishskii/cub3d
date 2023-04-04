/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 01:32:59 by sbritani          #+#    #+#             */
/*   Updated: 2022/10/18 00:09:44 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	rec_clear(t_list *cur, void (*del)(void *))
{
	if (cur->next)
		rec_clear(cur->next, del);
	del(cur->content);
	free(cur);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	rec_clear(lst[0], del);
	*lst = NULL;
}
