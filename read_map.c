/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:39:37 by sbritani          #+#    #+#             */
/*   Updated: 2023/03/06 10:30:27 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_map *read_map(t_settings *settings, char *map_path)
{
	int fd;
	t_map *res;

	res = malloc(sizeof(t_map));
	res->grid = malloc(sizeof(int*) * 30);
	res->x_size = 30;
	res->y_size = 30;
	int i = 0;
	int j = 0;
	while (i < 30)
	{
		res->grid[i] = malloc(sizeof(int) * 30);
		j = 0;
		while (j < 30)
		{
			res->grid[i][j] = ((i + j) * (i * j) % 7 == 0 || j == 0 || j == 29 || i == 0 || i == 29);
			j++;
		}
		i++;
	}
	return res;
}