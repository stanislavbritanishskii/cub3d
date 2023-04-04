/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:09:41 by sbritani          #+#    #+#             */
/*   Updated: 2022/10/18 21:01:32 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	int					res;
	const unsigned char	*s_1;
	const unsigned char	*s_2;

	s_1 = s1;
	s_2 = s2;
	i = 0;
	res = 0;
	while (i < n && res == 0)
	{
		res += s_1[i] - s_2[i];
		i++;
	}
	return (res);
}
