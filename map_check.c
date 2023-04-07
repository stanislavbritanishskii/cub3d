/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 22:50:25 by dhendzel          #+#    #+#             */
/*   Updated: 2023/04/07 23:00:47 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_map	*copy_map(t_map *orig)
{
	int		i;
	int		j;
	t_map	*res;

	res = malloc(sizeof(t_map));
	res->x_size = orig->x_size;
	res->y_size = orig->y_size;
	res->grid = malloc(sizeof(char *) * res->y_size);
	i = 0;
	while (i < res->y_size)
	{
		res->grid[i] = malloc(sizeof(char) * res->x_size);
		j = 0;
		while (j < res->x_size)
		{
			res->grid[i][j] = orig->grid[i][j];
			j++;
		}
		i++;
	}
	return (res);
}

bool	map_is_closed(t_map *map)
{
	t_map	*local;
	bool	res;
	int		x;
	int		y;

	local = copy_map(map);
	find_player(map, local, &x, &y);
	res = dfs(local, x, y);
	return (clean_map(local), res);
}

bool	dfs(t_map *map, int x, int y)
{
	if (map->grid[y][x] == '1')
		return (true);
	if (x == 0 || y == 0 || x == map->x_size - 1 || y == map->y_size - 1)
		return (false);
	else
	{
		map->grid[y][x] = '1';
		return (dfs(map, x + 1, y) * dfs(map, x - 1, y) * dfs(map, x, y + 1)
			* dfs(map, x, y - 1) * dfs(map, x + 1, y + 1)
			* dfs(map, x + 1, y - 1) * dfs(map, x - 1, y + 1)
			* dfs(map, x - 1, y - 1));
	}
}

void	find_player(t_map *map, t_map *local, int *x, int *y)
{
	bool	found;

	*y = 0;
	found = false;
	while (*y < local->y_size && !found)
	{
		*x = 0;
		while (*x < map->x_size && !found)
		{
			if (local->grid[*y][*x] == 'N' || local->grid[*y][*x] == 'S'
				|| local->grid[*y][*x] == 'W' || local->grid[*y][*x] == 'E')
			{
				found = true;
				map->grid[*y][*x] = '0';
			}
			if (!found)
				*x = *x + 1;
		}
		if (!found)
			*y = *y + 1;
	}
}
