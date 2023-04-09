/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 22:25:47 by dhendzel          #+#    #+#             */
/*   Updated: 2023/04/09 16:13:30 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	null_all(t_settings *res)
{
	res->map = NULL;
	res->dict = NULL;
	res->no = NULL;
	res->so = NULL;
	res->ea = NULL;
	res->we = NULL;
	res->point_of_view = NULL;
	res->observer_position = NULL;
}

t_settings	*init_settings(char *path)
{
	t_settings	*res;

	res = malloc(sizeof(t_settings));
	if (!res)
		return (NULL);
	null_all(res);
	if (!read_map(res, path))
		return (error_exit(res), NULL);
	if (!create_color(res, 'C') || !create_color(res, 'F'))
		return (error_exit(res), NULL);
	res->screame = mlx_load_png("./textures/screamer.png");
	res->no = mlx_load_png(dict_get(res->dict, "NO\0", "\0"));
	res->so = mlx_load_png(dict_get(res->dict, "SO\0", "\0"));
	res->ea = mlx_load_png(dict_get(res->dict, "EA\0", "\0"));
	res->we = mlx_load_png(dict_get(res->dict, "WE\0", "\0"));
	if (!res->no || !res->so || !res->ea || !res->we)
		return (error_exit(res), NULL);
	res->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	res->screamer = mlx_texture_to_image(res->mlx, res->screame);
	res->image = mlx_new_image(res->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(res->mlx, res->image, 0, 0);
	res->max_distance = MAX_DISTANCE;
	return (res);
}

void	error_exit(t_settings *settings)
{
	if (settings->dict)
		free_dict(settings->dict);
	if (settings->map)
		clean_map(settings->map);
	if (settings->no)
		mlx_delete_texture(settings->no);
	if (settings->so)
		mlx_delete_texture(settings->so);
	if (settings->ea)
		mlx_delete_texture(settings->ea);
	if (settings->we)
		mlx_delete_texture(settings->we);
	if (settings->observer_position)
		free(settings->observer_position);
	if (settings->point_of_view)
		free(settings->point_of_view);
	free(settings);
	ft_putstr_fd("Error\n", 2);
}
