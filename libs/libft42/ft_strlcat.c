/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:55:14 by sbritani          #+#    #+#             */
/*   Updated: 2022/10/24 02:34:02 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	if (!dst && !dstsize)
		return (0);
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = dst_len;
	while (i < dstsize && src[i - dst_len])
	{
		if (i == dstsize - 1)
			dst[i] = '\0';
		else
			dst[i] = src[i - dst_len];
		i++;
	}
	if (src[i - dst_len] == '\0')
		dst[i] = '\0';
	if (dstsize > dst_len)
		return (dst_len + src_len);
	return (dstsize + src_len);
}
