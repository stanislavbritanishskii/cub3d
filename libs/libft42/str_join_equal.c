/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join_equal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 02:58:29 by dhendzel          #+#    #+#             */
/*   Updated: 2023/03/06 10:47:23 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_two_strings(char *str1, char *str2)
{
	free(str1);
	free(str2);
}

char	*ft_str_join_free_first(char *str1, char *str2)
{
	char	*res;
	int		len1;
	int		len2;
	int		i;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (!str1 && !str2)
		return (NULL);
	res = malloc(sizeof(char) * (len1 + len2 + 1));
	i = -1;
	if (str1)
	{
		while (str1[++i])
			res[i] = str1[i];
	}
	i = -1;
	if (str2)
	{
		while (str2[++i])
			res[i + len1] = str2[i];
	}
	res[len1 + len2] = '\0';
	free(str1);
	return (res);
}

char	*ft_str_join_free_both(char *str1, char *str2)
{
	char	*res;
	int		len1;
	int		len2;
	int		i;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (!str1 && !str2)
		return (NULL);
	res = malloc(sizeof(char) * (len1 + len2 + 1));
	i = -1;
	if (str1)
	{
		while (str1[++i])
			res[i] = str1[i];
	}
	i = -1;
	if (str2)
	{
		while (str2[++i])
			res[i + len1] = str2[i];
	}
	res[len1 + len2] = '\0';
	free_two_strings(str1, str2);
	return (res);
}

int	strings_equal(char *str1, char *str2)
{
	int	i;

	if (!str1 && !str2)
		return (1);
	if (!str1 || !str2)
		return (0);
	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (str1[i] != str2[i])
		return (0);
	return (1);
}
