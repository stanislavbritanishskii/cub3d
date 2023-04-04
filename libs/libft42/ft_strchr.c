/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:16:07 by sbritani          #+#    #+#             */
/*   Updated: 2022/10/18 21:02:25 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int a)
{
	size_t	i;
	char	*res;
	char	c;

	i = 0;
	c = (char)a;
	res = (char *) s;
	while (s[i])
	{
		if (s[i] == c)
			return (res + i);
		i++;
	}
	if (s[i] == c)
		return (res + i);
	return (NULL);
}
