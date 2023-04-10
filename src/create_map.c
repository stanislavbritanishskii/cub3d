/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 22:39:58 by dhendzel          #+#    #+#             */
/*   Updated: 2023/04/10 02:45:31 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
		if ((int)ft_strlen(i_map[*height]) > width)
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
			if ((int)ft_strlen(i_map[height]) > iterator)
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
