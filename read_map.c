/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:39:37 by sbritani          #+#    #+#             */
/*   Updated: 2023/04/04 22:17:11 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <stdbool.h>

//t_map *read_map(t_settings *settings, char *map_path)
//{
//	int fd;
//	t_map *res;
//
//	res = malloc(sizeof(t_map));
//	res->grid = malloc(sizeof(int*) * 30);
//	res->x_size = 30;
//	res->y_size = 30;
//	int i = 0;
//	int j = 0;
//	while (i < 30)
//	{
//		res->grid[i] = malloc(sizeof(int) * 30);
//		j = 0;
//		while (j < 30)
//		{
//			res->grid[i][j] = (((i * j) % 3 == 0 && (i + j) % 3 != 1) || j == 0 || j == 29 || i == 0 || i == 29);
////			res->grid[i][j] = ((i + j) % 3 == 1 || j == 0 || j == 29 || i == 0 || i == 29);
//			j++;
//		}
//		i++;
//	}
//	return res;
//}

char **create_initial_map(int fd)
{
	char **res = NULL;
	char *str;
	int len;

	str = get_next_line(fd);
	while (str && ft_strlen(str) == 1)
	{
		free (str);
		str = get_next_line(fd);
	}

	len = 0;
	while (str)
	{
	printf("[%s]\n", str);
		res = add_string_to_string_arr(str, res, len);
		len++;
		free(str);
		str = get_next_line(fd);
	}
	return (res);
}

t_map *create_final_map(char **i_map)
{
	t_map *res;
	int width;
	int height;
	int iterator;

	height = 0;
	width = 0;
	res = malloc(sizeof(t_map));
	while (i_map[height])
	{
		if (ft_strlen(i_map[height]) > width)
			width = ft_strlen(i_map[height]);
		height ++;
	}
	res->y_size = height;
	res->x_size = width - 1;
	res->grid = malloc(sizeof (char *) * height);
	height --;
	while (height >= 0)
	{
		res->grid[height] = malloc(sizeof(char) * width);
		iterator = 0;
		while(iterator < width)
		{
			if (ft_strlen(i_map[height]) > iterator)
				res->grid[height][iterator] = (i_map[height][iterator]);
			else
				res->grid[height][iterator] = '0';

			if (res->grid[height][iterator] == ' ' || res->grid[height][iterator] == '\n')
				res->grid[height][iterator] = '0';

			iterator++;
		}
		height--;
	}
	ft_split_clear(i_map);
	return (res);
}

bool check_dict_filled(t_dict *dict)
{
	return (dict_get(dict, "NO\0", "\0")[0] *
		dict_get(dict, "SO\0", "\0")[0] *
		dict_get(dict, "EA\0", "\0")[0] *
		dict_get(dict, "WE\0", "\0")[0] *
		dict_get(dict, "F\0", "\0")[0] *
		dict_get(dict, "C\0", "\0")[0]);
}

int splitted_len(char **splitted)
{
	int i;

	if (!splitted)
		return 0;
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

bool	check_final_map(t_map *map)
{
	int x;
	int y;
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
				counter++;
			x++;
		}
		y++;
	}
	if (counter != 1)
		return(false);
	return (true);
}

bool read_map(t_settings* settings, char *path)
{
	t_dict *dict;
	t_map *res;
	char *str;
	char **splitted;
	char key[3];

	int fd;

//	dict_add(dict, "NO", "default");
	fd = open(path, O_RDONLY);
	dict = init_dict();
	str = get_next_line(fd);
	while (!check_dict_filled(dict) && str)
	{
		if (str[0] != '\n')
		{
			splitted = ft_split(str, " \n");

			if (splitted_len(splitted) != 2)
			{
				printf("111\n");
				ft_split_clear(splitted);
				free(str);
				free_dict(dict);
				return false;
			}
			if (!dict_get(dict, splitted[0], "\0")[0])
			{
				dict_add(dict, splitted[0], splitted[1]);
			}
			else
			{
				printf("222\n");
				ft_split_clear(splitted);
				free(str);
				free_dict(dict);
				return false;
			}
//			ft_split_clear(splitted);
		}
		free(str);
		str = get_next_line(fd);
	}
	if (!check_dict_filled(dict))
	{
		free_dict(dict);
		printf("333\n");
		return false;
	}
	settings->dict = dict;



	settings->map = create_final_map(create_initial_map(fd));
//	print_map(settings->map, 0, 0, 0, 0);
	if (!check_final_map(settings->map) || !map_is_closed(settings->map))
		return (false);
	// printf("################%d###################\n", (int)map_is_closed(settings->map));
	return (true);
}
