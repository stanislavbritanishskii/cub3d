/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 22:49:10 by dhendzel          #+#    #+#             */
/*   Updated: 2023/04/07 23:53:59 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

float	distance_to_grid(float a)
{
	if (a - (int)a > 0.5f || a - (int)a < -0.5f)
		return ((int)a + 1 - a);
	return (a - (int)a);
}

float	abs_float(float a)
{
	if (a < 0)
		return (-a);
	return (a);
}

float	min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

int	get_map_value(int x, int y, t_map *map)
{
	if (x < 0 || y < 0 || x >= map->x_size || y >= map->y_size)
		return (1);
	return (map->grid[y][x] - '0');
}
