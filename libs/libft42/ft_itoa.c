/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:44:04 by sbritani          #+#    #+#             */
/*   Updated: 2022/10/18 21:07:33 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n / 10 || n % 10)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static void	rec(long n, int len, char *res)
{
	if (n < 10)
		res[len] = n + '0';
	else
	{
		res[len] = n % 10 + '0';
		rec(n / 10, len - 1, res);
	}
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;
	int		size;
	long	nbr;

	len = 0;
	nbr = n;
	size = int_len(nbr);
	res = malloc((size + 1) * sizeof(char));
	if (!res)
		return (NULL);
	else
	{
		if (nbr < 0)
		{
			res[len++] = '-';
			nbr *= -1;
		}
		rec(nbr, size -1, res);
	}
	res[size] = '\0';
	return (res);
}
