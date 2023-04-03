/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:05:03 by sbritani          #+#    #+#             */
/*   Updated: 2023/03/05 19:15:43 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	map_extension_correct(char *map_path)
{
	int	i;

	i = 0;
	if (!map_path)
		return (0);
	while (map_path[i])
		i++;
	if (i < 5)
		return (0);
	return (strings_equal(map_path + i - 4, ".cub\0"));
}
