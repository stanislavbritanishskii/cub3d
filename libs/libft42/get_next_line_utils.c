/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:29:14 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/06 20:33:13 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	int		len;
// 	char	*res;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	len = ft_strlen(s1) + ft_strlen(s2);
// 	res = malloc(sizeof(char) * (len + 1));
// 	if (!res)
// 		return (NULL);
// 	while (s1[i] != 0)
// 	{
// 		res[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j] != 0)
// 	{
// 		res[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	res[len] = 0;
// 	return (res);
// }

int	ft_str_chr(const char *str, int c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_bzero(void *s, size_t len)
{
	size_t			i;
	unsigned char	*temp;

	i = 0;
	temp = s;
	while (i < len)
	{
		temp[i] = '\0';
		i++;
	}
}
