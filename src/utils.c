/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:09:05 by sbritani          #+#    #+#             */
/*   Updated: 2023/04/10 02:43:09 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	print_map(t_map *map, t_vector *player, t_vector *view)
{
	int	i;
	int	j;

	j = 0;
	while (j < map->y_size)
	{
		i = 0;
		while (i < map->x_size)
		{
			if ((int)player->x == i && (int)player->y == j)
				printf("\033[31mP\033[0m");
			else if ((int)view->x == i && (int)view->y == j)
				printf("\033[34mV\033[0m");
			else
				printf("%c", map->grid[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
}

t_vector	get_ray_direction(t_vector observer_position,
	t_vector point_of_view, float angle)
{
	t_vector	ray_direction;
	t_vector	ray_direction_rotated;
	float		sin_angle;
	float		cos_angle;
	float		length;

	ray_direction.x = point_of_view.x - observer_position.x;
	ray_direction.y = point_of_view.y - observer_position.y;
	length = sqrtf(ray_direction.x * ray_direction.x
			+ ray_direction.y * ray_direction.y);
	ray_direction.x /= length;
	ray_direction.y /= length;
	sin_angle = sinf(angle);
	cos_angle = cosf(angle);
	ray_direction_rotated.x = cos_angle * ray_direction.x
		+ sin_angle * ray_direction.y;
	ray_direction_rotated.y = -sin_angle * ray_direction.x
		+ cos_angle * ray_direction.y;
	return (ray_direction_rotated);
}

bool	incredible_check(t_vector position,
		t_map *map)
{
	int	map_x;
	int	map_y;

	map_x = (int)position.x;
	map_y = (int)position.y;
	return ((abs_float(distance_to_grid(position.x))
			< abs_float(distance_to_grid(position.y))
			&& (get_map_value((int)(position.x + RAY_STEP_SIZE),
				map_y, map) == 1
			|| get_map_value((int)(position.x - RAY_STEP_SIZE),
			map_y, map) == 1))
			|| (get_map_value(map_x, (int)(position.y + RAY_STEP_SIZE),
				map) == 0
			&& get_map_value(map_x, (int)(position.y - RAY_STEP_SIZE),
				map) == 0));
}

void	hit_a_wall(t_vector position, t_vector direction,
		t_map *map, t_march_return *res)
{
	int	map_x;
	int	map_y;

	map_x = (int)position.x;
	map_y = (int)position.y;
	while (get_map_value(map_x, map_y, map) == 1)
	{
		res->distance -= RAY_STEP_SIZE;
		position.x -= direction.x * RAY_STEP_SIZE;
		position.y -= direction.y * RAY_STEP_SIZE;
		map_x = (int)position.x;
		map_y = (int)position.y;
	}
	if (incredible_check(position, map))
	{
		res->shift = abs_float(position.y - (int)position.y);
		res->direction = 1 + (position.x - (int)position.x > 0.5f);
	}
	else
	{
		res->shift = abs_float(position.x - (int) position.x);
		res->direction = 3 + (position.y - (int)position.y > 0.5f);
	}		
}

t_march_return	*ray_march(t_settings *settings,
		t_vector direction, t_map *map, t_march_return *res)
{
	float		step;
	int			map_x;
	int			map_y;
	t_vector	position;

	position.x = settings->observer_position->x;
	position.y = settings->observer_position->y;
	step = RAY_STEP_SIZE;
	res->distance = 0;
	while (res->distance < settings->max_distance)
	{
		map_x = (int)position.x;
		map_y = (int)position.y;
		if (get_map_value(map_x, map_y, map) == 1)
			return (hit_a_wall(position, direction, map, res), res);
		step = RAY_STEP_SIZE * (1 + 9 * (res->distance >= BIG_DISTANCE)
				* (1 + 9 * (res->distance >= BIG_DISTANCE * 10)));
		res->distance += step;
		position.x += direction.x * step;
		position.y += direction.y * step;
	}
	res->distance = settings->max_distance;
	res->shift = 0.5f;
	res->direction = 5;
	return (res);
}
