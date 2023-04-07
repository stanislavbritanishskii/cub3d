/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:39:37 by sbritani          #+#    #+#             */
/*   Updated: 2023/04/07 22:10:19 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	**create_initial_map(int fd)
{
	char	**res;
	char	*str;
	int		len;

	res = NULL;
	str = get_next_line(fd);
	while (str && ft_strlen(str) == 1)
	{
		free (str);
		str = get_next_line(fd);
	}
	len = 0;
	while (str)
	{
		res = add_string_to_string_arr(str, res, len);
		len++;
		free(str);
		str = get_next_line(fd);
	}
	return (res);
}

void	get_max_width(t_map *res, int *height, char **i_map)
{
	int	width;

	width = 0;
	*height = 0;
	while (i_map[*height])
	{
		if (ft_strlen(i_map[*height]) > width)
			width = ft_strlen(i_map[*height]);
		*height = *height + 1;
	}
	res->y_size = *height;
	res->x_size = width - 1;
	res->grid = malloc(sizeof (char *) * *height);
	*height = *height - 1;
}

t_map	*create_final_map(char **i_map)
{
	t_map	*res;
	int		height;
	int		iterator;

	res = malloc(sizeof(t_map));
	get_max_width(res, &height, i_map);
	while (height >= 0)
	{
		res->grid[height] = malloc(sizeof(char) * res->x_size + 1);
		iterator = 0;
		while (iterator < res->x_size + 1)
		{
			if (ft_strlen(i_map[height]) > iterator)
				res->grid[height][iterator] = (i_map[height][iterator]);
			else
				res->grid[height][iterator] = '0';
			if (res->grid[height][iterator] == ' '
				|| res->grid[height][iterator] == '\n')
				res->grid[height][iterator] = '0';
			iterator++;
		}
		height--;
	}
	ft_split_clear(i_map);
	return (res);
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

int	splitted_len(char **splitted)
{
	int	i;

	if (!splitted)
		return (0);
	i = 0;
	while (splitted[i])
	{
		i++;
	}
	return (i);
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

void	free_vectors(t_settings *settings)
{
	if (settings->observer_position)
		free(settings->observer_position);
	settings->observer_position = NULL;
	if (settings->point_of_view)
		free(settings->point_of_view);
	settings->point_of_view = NULL;
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
