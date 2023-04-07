/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:39:37 by sbritani          #+#    #+#             */
/*   Updated: 2023/04/07 23:54:05 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	set_player(t_settings *settings, t_map *map, int x, int y)
{
	settings->observer_position = malloc(sizeof(t_vector));
	settings->point_of_view = malloc(sizeof(t_vector));
	settings->observer_position->x = x + 0.5f;
	settings->observer_position->y = y + 0.5f;
	if (map->grid[y][x] == 'N')
	{
		settings->point_of_view->x = x + 0.5f;
		settings->point_of_view->y = y + 0.5 - VIEW_POINT_DIST;
	}
	if (map->grid[y][x] == 'S')
	{
		settings->point_of_view->x = x + 0.5f;
		settings->point_of_view->y = y + 0.5 + VIEW_POINT_DIST;
	}
	if (map->grid[y][x] == 'E')
	{
		settings->point_of_view->x = x + 0.5f + VIEW_POINT_DIST;
		settings->point_of_view->y = y + 0.5;
	}
	if (map->grid[y][x] == 'W')
	{
		settings->point_of_view->x = x + 0.5f - VIEW_POINT_DIST;
		settings->point_of_view->y = y + 0.5;
	}
}

void	read_map_error(char *str, t_dict *dict)
{
	ft_putstr_fd("Wrong map\n", 2);
	free(str);
	free_dict(dict);
}

bool	add_to_dict(char *str, t_dict *dict)
{
	char	**splitted;

	splitted = ft_split(str, " \n");
	if (splitted_len(splitted) != 2)
		return (ft_split_clear(splitted), false);
	if (!dict_get(dict, splitted[0], "\0")[0])
		dict_add(dict, splitted[0], splitted[1]);
	else
		return (ft_split_clear(splitted), false);
	ft_split_clear(splitted);
	return (true);
}

bool	initial_parsing(t_dict *dict, char *path, int fd)
{
	char	*str;

	str = get_next_line(fd);
	while (!check_dict_filled(dict) && str)
	{
		if (str[0] != '\n')
		{
			if (!add_to_dict(str, dict))
				return (read_map_error(str, dict), false);
		}
		free(str);
		str = get_next_line(fd);
	}
	if (!check_dict_filled(dict))
		return (free_dict(dict), false);
	if (str)
		free(str);
	return (true);
}

bool	read_map(t_settings *settings, char *path)
{
	t_map	*res;
	t_dict	*dict;
	int		fd;

	fd = open(path, 'r');
	if (fd < 0)
		return (false);
	dict = init_dict();
	if (!initial_parsing(dict, path, fd))
		return (false);
	settings->dict = dict;
	settings->map = create_final_map(create_initial_map(fd));
	if (!check_final_map(settings->map, settings)
		|| !map_is_closed(settings->map))
		return (free_vectors(settings), false);
	return (true);
}
