/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:54:31 by sbritani          #+#    #+#             */
/*   Updated: 2023/04/10 02:44:36 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	ft_hook(void *param)
{
	t_settings		*settings;

	settings = param;
	check_music(settings);
	print_map(settings->map, settings->observer_position,
		settings->point_of_view);
	if (mlx_is_key_down(settings->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(settings->mlx);
	if (mlx_is_key_down(settings->mlx, MLX_KEY_D))
		move_character(settings, RIGHT);
	if (mlx_is_key_down(settings->mlx, MLX_KEY_A))
		move_character(settings, LEFT);
	if (mlx_is_key_down(settings->mlx, MLX_KEY_W))
		move_character(settings, FORWARD);
	if (mlx_is_key_down(settings->mlx, MLX_KEY_S))
		move_character(settings, BACKWARD);
	if (mlx_is_key_down(settings->mlx, MLX_KEY_RIGHT))
		rotate_point(settings, TURN_ANGLE);
	if (mlx_is_key_down(settings->mlx, MLX_KEY_LEFT))
		rotate_point(settings, -TURN_ANGLE);
	if (mlx_is_key_down(settings->mlx, MLX_KEY_Z))
		reset_view(settings);
	draw_sky_floor(settings);
	draw_walls(settings);
	usleep(20000);
}

int	main(int argc, char **argv)
{
	t_settings	*settings = NULL;

	if (argc == 2)
		settings = init_settings(argv[1]);
	else
		ft_putstr_fd("Error\nWrong input\n", 2);
	if (settings)
	{
		draw_sky_floor(settings);
		mlx_loop_hook(settings->mlx, ft_hook, settings);
		mlx_loop(settings->mlx);
		clean_settings(settings);
		return (0);
	}
	return (1);
}
