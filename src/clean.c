/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 22:35:46 by dhendzel          #+#    #+#             */
/*   Updated: 2023/04/07 23:53:40 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	clean_map(t_map *map)
{
	int	y;

	y = 0;
	while (y < map->y_size)
	{
		free(map->grid[y]);
		y++;
	}
	free(map->grid);
	free(map);
}

void	clean_settings(t_settings *settings)
{
	free_dict(settings->dict);
	clean_map(settings->map);
	mlx_delete_texture(settings->no);
	mlx_delete_texture(settings->so);
	mlx_delete_texture(settings->ea);
	mlx_delete_texture(settings->we);
	if (settings->observer_position)
		free(settings->observer_position);
	if (settings->point_of_view)
		free(settings->point_of_view);
	free(settings);
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
