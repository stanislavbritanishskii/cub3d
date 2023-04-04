/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 01:25:01 by sbritani          #+#    #+#             */
/*   Updated: 2022/10/18 00:09:12 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst[0])
	{
		lst[0] = new;
		return ;
	}
	temp = lst[0];
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new;
}
