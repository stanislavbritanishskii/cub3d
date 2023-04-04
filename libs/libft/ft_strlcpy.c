/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:41:43 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/04 02:48:58 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < dstsize)
	{
		if (i < dstsize)
		{
			if (i == dstsize - 1)
				dst[i] = '\0';
			else
				dst[i] = src[i];
		}
		i++;
	}
	if (src[i] == '\0')
		dst[i] = '\0';
	return (ft_strlen(src));
}
