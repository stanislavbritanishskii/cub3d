/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:26:33 by sbritani          #+#    #+#             */
/*   Updated: 2022/10/18 21:10:01 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int a)
{
	size_t	i;
	char	*res;
	char	c;

	c = (char)a;
	i = ft_strlen(s);
	res = (char *) s;
	while (i > 0)
	{
		if (s[i] == c)
			return (res + i);
		i--;
	}
	if (s[i] == c)
		return (res + i);
	return (NULL);
}
