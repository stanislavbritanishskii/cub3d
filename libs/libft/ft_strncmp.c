/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:43:15 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/07 03:55:32 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		res;

	if (!s1 || !s2)
		return (1);
	i = 0;
	res = 0;
	while (i < n && res == 0 && (s1[i] != '\0' || s2[i] != '\0'))
	{
		res += (unsigned char)s1[i] - (unsigned char)s2[i];
		i++;
	}
	return (res);
}
