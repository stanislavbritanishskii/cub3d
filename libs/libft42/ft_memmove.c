/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 23:15:35 by sbritani          #+#    #+#             */
/*   Updated: 2022/10/25 23:16:23 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*s1;
	const char	*s2;

	i = 0;
	s1 = (char *)dst;
	s2 = (const char *)src;
	if (dst < src)
	{
		while (i < len)
		{
			s1[i] = s2[i];
			i++;
		}
	}
	else if (dst > src)
	{
		while (len > 0)
		{
			len--;
			s1[len] = s2[len];
		}
	}
	return (s1);
}
