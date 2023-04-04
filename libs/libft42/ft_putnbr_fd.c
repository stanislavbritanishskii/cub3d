/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 23:38:11 by sbritani          #+#    #+#             */
/*   Updated: 2022/10/18 00:07:10 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else
	{
		if (nb < 0)
		{
			ft_putchar_fd('-', fd);
			ft_putnbr_fd(nb * -1, fd);
		}
		else
		{
			if (nb < 10)
				ft_putchar_fd((char)(nb + 48), fd);
			else
			{
				ft_putnbr_fd(nb / 10, fd);
				ft_putchar_fd((char)(nb % 10 + 48), fd);
			}
		}
	}
}
