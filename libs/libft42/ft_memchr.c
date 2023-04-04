/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:50:13 by sbritani          #+#    #+#             */
/*   Updated: 2022/10/18 21:01:20 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int a, size_t n)
{
	size_t	i;
	char	*res;
	char	c;

	i = 0;
	c = (char)a;
	res = (char *) s;
	while (i < n)
	{
		if (res[i] == c)
			return (res + i);
		i++;
	}
	return (NULL);
}
