/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:09:05 by sbritani          #+#    #+#             */
/*   Updated: 2023/04/05 12:58:32 by dhendzel         ###   ########.fr       */
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
	int i;
	int j;

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
//		printf("\n");
		j++;
	}
}

int getMapValue(int x, int y, t_map *map)
{
	if (x < 0 || y < 0 || x >= map->x_size || y >= map->y_size) {
		return 1;
	}
	return map->grid[y][x] - '0';
}

t_vector getRayDirection(t_vector observerPosition, t_vector pointOfView, float angle)
{
	t_vector rayDirection;
	rayDirection.x = pointOfView.x - observerPosition.x;
	rayDirection.y = pointOfView.y - observerPosition.y;
	float length = sqrtf(rayDirection.x * rayDirection.x + rayDirection.y * rayDirection.y);
	rayDirection.x /= length;
	rayDirection.y /= length;

	float sinAngle = sinf(angle);
	float cosAngle = cosf(angle);

	t_vector rayDirectionRotated = {
			cosAngle * rayDirection.x + sinAngle * rayDirection.y,
			-sinAngle * rayDirection.x + cosAngle * rayDirection.y
	};
	return rayDirectionRotated;
}

float distance_to_grid(float a)
{
	if (a - (int)a > 0.5f || a - (int)a < -0.5f)
		return ((int)a + 1 - a);
	return (a - (int)a);
}

float abs_float(float a)
{
	if (a < 0)
		return (-a);
	return (a);
}



t_march_return *rayMarch(t_vector position, t_vector direction, t_map *map, t_march_return *res)
{
	float distance = 0;
	float step = RAY_STEP_SIZE;

	while (distance < MAX_DISTANCE) {
		int mapX = (int)position.x;
		int mapY = (int)position.y;
		if (getMapValue(mapX, mapY, map) == 1)
		{

			while (getMapValue(mapX, mapY, map) == 1)
			{
				distance -= RAY_STEP_SIZE;
				position.x -= direction.x * RAY_STEP_SIZE;
				position.y -= direction.y * RAY_STEP_SIZE;
				mapX = (int)position.x;
				mapY = (int)position.y;
			}
			if ((abs_float(distance_to_grid(position.x)) < abs_float(distance_to_grid(position.y)) &&
					(getMapValue((int) (position.x + RAY_STEP_SIZE), mapY, map) == 1 || getMapValue((int) (position.x - RAY_STEP_SIZE), mapY, map) == 1)) || (getMapValue(mapX, (int)(position.y + RAY_STEP_SIZE), map) == 0 && getMapValue(mapX, (int)(position.y - RAY_STEP_SIZE), map) == 0))
			{
				res->shift = abs_float(position.y - (int)position.y);
				res->direction = 1 + (position.x - (int)position.x > 0.5f);
			}
			else
			{
				res->shift = abs_float(position.x - (int) position.x);
				res->direction = 3 + (position.y - (int)position.y > 0.5f);
			}
			res->distance = distance;
			return res;
		}
		if (distance >= BIG_DISTANCE)
			step = RAY_STEP_SIZE * 10;
		if (distance >= BIG_DISTANCE * 10)
			step = RAY_STEP_SIZE * 100;
		distance += step;
		position.x += direction.x * step;
		position.y += direction.y * step;
	}
	res->distance = MAX_DISTANCE;
	res->shift = 0.5f;
	res->direction = 5;
	return (res);
}





t_map *copy_map(t_map *orig)
{
	int i;
	int j;
	t_map *res;

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

bool dfs(t_map *map, int x, int y)
{
	// print_map(map, 0, 0, (float)x, (float)y);
	if (map->grid[y][x] == '1')
		return true;
	if (x == 0 || y == 0 || x == map->x_size - 1 || y == map->y_size - 1)
		return false;
	else
	{
		map->grid[y][x] = '1';
		return (dfs(map, x + 1, y) * dfs(map, x - 1, y) * dfs(map, x, y + 1) *
		dfs(map, x, y - 1) * dfs(map, x + 1, y + 1) * dfs(map, x + 1, y - 1) *
		dfs(map, x - 1, y + 1) * dfs(map, x - 1, y - 1));
	}
}

bool map_is_closed(t_map *map)
{
	t_map *local;
	int x;
	int y;
	bool found;
	bool res;

	local = copy_map(map);
	y = 0;
	found = false;
	while (y < local->y_size && !found)
	{

		x = 0;
		while (x < map->x_size && !found)
		{
			if (local->grid[y][x] == 'N' || local->grid[y][x] == 'S' || local->grid[y][x] == 'W' || local->grid[y][x] == 'E') {
				found = true;
				map->grid[y][x] = '0';
			}
			if (!found)
				x++;
		}
		if (!found)
			y++;
	}
	res = dfs(local, x, y);
	clean_map(local);
	return (res);
}


//float rayMarch(t_vector position, t_vector direction, t_map *map) {
//	float distance = 0;
//	int mapX = (int) position.x;
//	int mapY = (int) position.y;
//	float stepX = 1.0 / fabs(direction.x);
//	float stepY = 1.0 / fabs(direction.y);
//	float nextX = (direction.x > 0) ? ceil(position.x) : floor(position.x);
//	float nextY = (direction.y > 0) ? ceil(position.y) : floor(position.y);
//	float deltaX = fabs(nextX - position.x);
//	float deltaY = fabs(nextY - position.y);
//
//	while (distance < MAX_DISTANCE) {
//		if (deltaX < deltaY) {
//			distance += deltaX;
//			position.x = nextX;
//			nextX += (direction.x > 0) ? 1 : -1;
//			mapX = (int) position.x;
//			if (getMapValue(mapX, mapY, map) == 1) {
//				return distance;
//			}
//			deltaX = fabs(nextX - position.x);
//		} else {
//			distance += deltaY;
//			position.y = nextY;
//			nextY += (direction.y > 0) ? 1 : -1;
//			mapY = (int) position.y;
//			if (getMapValue(mapX, mapY, map) == 1) {
//				return distance;
//			}
//			deltaY = fabs(nextY - position.y);
//		}
//	}
//
//	return MAX_DISTANCE;
//}
