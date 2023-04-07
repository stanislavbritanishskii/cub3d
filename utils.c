/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:09:05 by sbritani          #+#    #+#             */
/*   Updated: 2023/04/07 21:27:27 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//char **read_lines(char *path)
//{
//	int		fd;
//	char	**res;
//	char	*line;
//	int		i;
//
//	res = NULL;
//	fd = open(path, O_RDONLY);
//	if (fd < 0)
//		return (NULL);
//	line = readline(fd);
//	i = 0;
//	while (line)
//	{
//		res = add_string_to_string_arr(line, res, i);
//		i++;
//		line = readline(fd);
//	}
//	return (res);
//}

int	check_wall_down(float x, float y, t_map *map)
{
	int	x_;
	int	y_;

	x_ = (int)x;
	y_ = (int)y;
	y_++;
	if (x_ < map->x_size && y_ < map->y_size && map->grid[y_][x_] == 1)
		return (1);
	return (0);
}

int	check_wall_up(float x, float y, t_map *map)
{
	int	x_;
	int	y_;

	x_ = (int)x;
	y_ = (int)y;
	y_--;
	if (x_ < map->x_size && y_ >= 0 && map->grid[y_][x_] == 1)
		return (1);
	return (0);
}

int	check_wall_right(float x, float y, t_map *map)
{
	int	x_;
	int	y_;

	x_ = (int)x;
	x_++;
	y_ = (int)y;
	if (x_ < map->x_size && y_ < map->y_size && map->grid[y_][x_] == 1)
		return (1);
	return (0);
}

int	check_wall_left(float x, float y, t_map *map)
{
	int	x_;
	int	y_;

	x_ = (int)x;
	x_--;
	y_ = (int)y;
	if (x_ >= 0 && y_ < map->y_size && map->grid[y_][x_] == 1)
		return (1);
	return (0);
}

void	print_map(t_map *map, float x, float y, float x2, float y2)
{
	int	i;
	int	j;

	j = 0;
	while (j < map->y_size)
	{
		i = 0;
		while (i < map->x_size)
		{
			if ((int)x == i && (int)y == j)
				printf("\033[31mP\033[0m");
			else if ((int)x2 == i && (int)y2 == j)
				printf("\033[34mV\033[0m");
			else
				printf("%c", map->grid[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
}

int	get_map_value(int x, int y, t_map *map)
{
	if (x < 0 || y < 0 || x >= map->x_size || y >= map->y_size)
		return (1);
	return (map->grid[y][x] - '0');
}

t_vector	get_ray_direction(t_vector observerPosition,
	t_vector pointOfView, float angle)
{
	t_vector	ray_direction;
	t_vector	ray_direction_rotated;
	float		sin_angle;
	float		cos_angle;
	float		length;

	ray_direction.x = pointOfView.x - observerPosition.x;
	ray_direction.y = pointOfView.y - observerPosition.y;
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

bool	incredible_check(t_vector position, t_vector direction,
		t_map *map, t_march_return *res)
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
	if (incredible_check(position, direction, map, res))
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

t_march_return	*ray_march(t_vector position,
		t_vector direction, t_map *map, t_march_return *res)
{
	float	step;
	int		map_x;
	int		map_y;

	step = RAY_STEP_SIZE;
	res->distance = 0;
	while (res->distance < MAX_DISTANCE)
	{
		map_x = (int)position.x;
		map_y = (int)position.y;
		if (get_map_value(map_x, map_y, map) == 1)
			return (hit_a_wall(position, direction, map, res), res);
		if (res->distance >= BIG_DISTANCE)
			step = RAY_STEP_SIZE * 10;
		if (res->distance >= BIG_DISTANCE * 10)
			step = RAY_STEP_SIZE * 100;
		res->distance += step;
		position.x += direction.x * step;
		position.y += direction.y * step;
	}
	res->distance = MAX_DISTANCE;
	res->shift = 0.5f;
	res->direction = 5;
	return (res);
}

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
