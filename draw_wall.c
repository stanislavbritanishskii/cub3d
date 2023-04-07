/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 22:29:53 by dhendzel          #+#    #+#             */
/*   Updated: 2023/04/07 22:46:52 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	put_pixel(t_settings *settings, int x, int y, uint32_t color)
{
	mlx_put_pixel(settings->image, x, y, color);
}

void	draw_line_floor_sky(t_settings *settings, int x)
{
	int		i;
	int		color;
	float	darkness;

	i = 0;
	while (i < HEIGHT / 2)
	{
		darkness = 1 - (((float)RANDOM
					/ ((float)HEIGHT / 2 - i)) / (float) MAX_DISTANCE);
		if (darkness < 0)
			darkness = 0;
		color = get_color(settings->ceiling_color, darkness);
		put_pixel(settings, x, i, color);
		i++;
	}
	while (i < HEIGHT)
	{
		darkness = 1 - (((float)RANDOM
					/ ((float)i - (float)HEIGHT / 2)) / (float) MAX_DISTANCE);
		if (darkness < 0)
			darkness = 0;
		color = get_color(settings->floor_color, darkness);
		put_pixel(settings, x, i, color);
		i++;
	}
}

void	draw_direction(t_settings *settings, t_march_return *march, float d)
{
	t_texture	texture;

	texture.height = RANDOM / (march->distance + SMALL);
	texture.x_shift = march->shift;
	texture.d = d;
	if (march->direction == SO)
		draw_texture_line(settings, settings->so, &texture);
	if (march->direction == EA)
		draw_texture_line(settings, settings->ea, &texture);
	if (march->direction == NO)
		draw_texture_line(settings, settings->no, &texture);
	if (march->direction == WE)
		draw_texture_line(settings, settings->we, &texture);
	if (march->direction == 5)
		draw_line_floor_sky(settings, d);
}

void	draw_walls(t_settings *settings)
{
	float			d;
	float			angle;
	t_vector		direction;
	t_march_return	march;

	d = WIDTH;
	angle = -0.15f * M_PI;
	while (d >= 0)
	{
		direction = get_ray_direction(*settings->observer_position,
				*settings->point_of_view, angle);
		ray_march(*settings->observer_position,
			direction, settings->map, &march);
		march.distance *= cosf(angle);
		draw_direction(settings, &march, d);
		d = d - 1;
		angle += 0.3f * M_PI / WIDTH;
	}
}

void	draw_sky_floor(t_settings *settings, bool start)
{
	float		d;

	d = WIDTH;
	while (d >= 0)
	{
		draw_line_floor_sky(settings, d);
		d--;
	}
}
