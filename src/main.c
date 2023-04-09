/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:54:31 by sbritani          #+#    #+#             */
/*   Updated: 2023/04/09 22:08:55 by dhendzel         ###   ########.fr       */
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
	draw_sky_floor(settings, false);
	draw_walls(settings);
	usleep(20000);
}
//  void autopilot(void *param)
//  {
//  	t_settings* settings = param;
// 	 	t_march_return march;
//  	print_map(settings->map, settings->observer_position->x,
// 			settings->observer_position->y, 
//		settings->point_of_view->x, settings->point_of_view->y);
// 	 	draw_sky_floor(settings, false);
//  	float angle = -0.5f * M_PI;
//  	t_vector direction = get_ray_direction#(*settings->observer_position,
// *settings->point_of_view, angle);
//  	ray_march(*settings->observer_position,
		// direction, settings->map, &march);
// 	float distance = march.distance;
//  	angle = 0;
//  	direction = get_ray_direction#(*settings->observer_position,
//		*settings->point_of_view, angle);
//  	ray_march(*settings->observer_position,
	//  direction, settings->map, &march);
// 	float distance2 = march.distance;
//  	angle = 0.5f * M_PI;
//  	direction = get_ray_direction#(*settings->observer_position, 
//			*settings->point_of_view, angle);
//  	ray_march(*settings->observer_position,
// direction, settings->map, &march);
// 	float distance3 = march.distance;
//  	if (distance3 + distance + distance2 < 1) {
// 		rotate_point(settings, 0.06f);
// 		move_character(settings, BACKWARD);
// 	}
//  	else if (distance > distance2 && distance > distance3)
//  		rotate_point(settings, 0.02f);
//  	else if (distance3 > distance2 && distance3 > distance)
//  		rotate_point(settings, -0.02f);
// //	 if (distance2 > 0.5f)
// 	move_character(settings, FORWARD);
// 	 draw_walls(settings);
//  }

void	check_leaks(void)
{
	system("leaks cub3d");
}

int	main(int argc, char **argv)
{
	t_settings	*settings;

	atexit(check_leaks);
	if (argc == 2)
		settings = init_settings(argv[1]);
	else
		ft_putstr_fd("Error\nWrong input\n", 2);
	if (settings)
	{
		draw_sky_floor(settings, true);
		mlx_loop_hook(settings->mlx, ft_hook, settings);
		mlx_loop(settings->mlx);
		clean_settings(settings);
		return (0);
	}
	return (1);
}
