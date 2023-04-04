/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:23:15 by sbritani          #+#    #+#             */
/*   Updated: 2022/10/24 02:35:40 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	if (!haystack && !len)
		return (NULL);
	needle_len = ft_strlen(needle);
	if (ft_strlen(haystack) < needle_len)
		return (NULL);
	if (needle_len == 0)
		return ((char *)haystack);
	if (len == 0 || needle_len > len)
		return (NULL);
	i = 0;
	while (i <= len && i <= len - needle_len
		&& (char)*(haystack + needle_len - 1) != '\0')
	{
		if (0 == ft_strncmp(haystack, needle, needle_len))
			return ((char *)haystack);
			haystack++;
			i++;
	}
	return (NULL);
}
