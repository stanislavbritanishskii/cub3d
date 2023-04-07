/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:05:03 by sbritani          #+#    #+#             */
/*   Updated: 2023/04/07 23:53:34 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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

bool	is_player(char element)
{
	if (element == 'S' || element == 'E' || element == 'W' || element == 'N')
		return (true);
	else
		return (false);
}

bool	wrong_char(char element)
{
	if (element == '1' || element == '0' || is_player(element))
		return (false);
	else
		return (true);
}

bool	check_dict_filled(t_dict *dict)
{
	return (dict_get(dict, "NO\0", "\0")[0] *
		dict_get(dict, "SO\0", "\0")[0] *
		dict_get(dict, "EA\0", "\0")[0] *
		dict_get(dict, "WE\0", "\0")[0] *
		dict_get(dict, "F\0", "\0")[0] *
		dict_get(dict, "C\0", "\0")[0]);
}

bool	check_final_map(t_map *map, t_settings *settings)
{
	int	x;
	int	y;
	int	counter;

	counter = 0;
	y = 0;
	while (y < map->y_size)
	{
		x = 0;
		while (x < map->x_size)
		{
			if (wrong_char(map->grid[y][x]))
				return (false);
			if (is_player(map->grid[y][x]))
			{
				if (!counter++)
					set_player(settings, map, x, y);
			}
			x++;
		}
		y++;
	}
	if (counter != 1)
		return (false);
	return (true);
}
