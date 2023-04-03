/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:09:05 by sbritani          #+#    #+#             */
/*   Updated: 2023/03/06 10:57:45 by sbritani         ###   ########.fr       */
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

	i = 0;
	while (i < map->x_size)
	{
		j = 0;
		while (j < map->y_size)
		{
			if ((int)x == j && (int)y == i)
				printf("\033[31mX\033[0m");
			else if ((int)x2 == j && (int)y2 == i)
				printf("\033[34mX\033[0m");
			else
				printf("%d", map->grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int getMapValue(int x, int y, t_map *map)
{
	if (x < 0 || y < 0 || x >= map->x_size || y >= map->y_size) {
		return 1;  // Assume walls surround the map to prevent going out of bounds
	}
	return map->grid[x][y];
}

t_vector getRayDirection(t_vector observerPosition, t_vector pointOfView, float angle) {
	t_vector rayDirection;
	rayDirection.x = pointOfView.x - observerPosition.x;
	rayDirection.y = pointOfView.y - observerPosition.y;
	float length = sqrt(rayDirection.x * rayDirection.x + rayDirection.y * rayDirection.y);
	rayDirection.x /= length;
	rayDirection.y /= length;

	float sinAngle = sin(angle);
	float cosAngle = cos(angle);

	// Rotate the ray direction vector by the specified angle
	t_vector rayDirectionRotated = {
			cosAngle * rayDirection.x + sinAngle * rayDirection.y,
			-sinAngle * rayDirection.x + cosAngle * rayDirection.y
	};
	return rayDirectionRotated;
}

float rayMarch(t_vector position, t_vector direction, t_map *map) {
	float distance = 0;
	while (distance < MAX_DISTANCE) {
		int mapX = (int)position.x;
		int mapY = (int)position.y;
		if (getMapValue(mapX, mapY, map) == 1) {
			return distance;  // Hit a wall
		}
		distance += STEP_SIZE;
		position.x += direction.x * STEP_SIZE;
		position.y += direction.y * STEP_SIZE;
	}
	return MAX_DISTANCE;  // Didn't hit anything within the maximum distance
}