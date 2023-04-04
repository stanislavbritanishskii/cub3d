/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 23:55:36 by sbritani          #+#    #+#             */
/*   Updated: 2022/10/17 22:45:01 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*res;

	if ((size_t)ft_strlen((char *)s) > len)
		res = malloc((len + 1) * sizeof(char));
	else
		res = malloc((ft_strlen((char *)s) + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < start && s[i])
		i++;
	while (j < len && s[i])
	{
		res[j] = s[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}
