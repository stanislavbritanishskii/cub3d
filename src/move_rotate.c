/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 22:33:38 by dhendzel          #+#    #+#             */
/*   Updated: 2023/04/07 23:54:01 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	reset_view(t_settings *settings)
{
	settings->point_of_view->y = settings->observer_position->y
		+ VIEW_POINT_DIST;
		settings->point_of_view->x = settings->observer_position->x;
}

void	move(t_settings *settings, float x, float y)
{
	if (settings->map->grid[(int)(settings->observer_position->y)]
		[(int)(settings->observer_position->x + x)] == '0')
	{
		settings->observer_position->x += x;
		settings->point_of_view->x += x;
		if (settings->map->grid[(int)(settings->observer_position->y + y)]
			[(int)(settings->observer_position->x)] == '0')
		{
			settings->observer_position->y += y;
			settings->point_of_view->y += y;
		}
	}
	else if (settings->map->grid[(int)(settings->observer_position->y + y)]
		[(int)(settings->observer_position->x)] == '0')
	{
		settings->observer_position->y += y;
		settings->point_of_view->y += y;
		if (settings->map->grid[(int)(settings->observer_position->y)]
			[(int)(settings->observer_position->x + x)] == '0')
		{
			settings->observer_position->x += x;
			settings->point_of_view->x += x;
		}
	}
}

void	move_character(t_settings *settings, float move_dir)
{
	float	d_x;
	float	d_y;
	float	delta;

	d_x = settings->point_of_view->x - settings->observer_position->x;
	d_y = settings->point_of_view->y - settings->observer_position->y;
	delta = STEP_SIZE;
	d_x *= delta;
	d_y *= delta;
	if (move_dir == FORWARD)
		move(settings, d_x, d_y);
	else if (move_dir == BACKWARD)
		move(settings, -d_x, -d_y);
	else if (move_dir == LEFT)
		move(settings, d_y, -d_x);
	else if (move_dir == RIGHT)
		move(settings, -d_y, d_x);
}

void	rotate_point(t_settings *settings, float theta)
{
	t_rotation	rotate;

	rotate.x = settings->point_of_view->x - settings->observer_position->x;
	rotate.y = settings->point_of_view->y - settings->observer_position->y;
	rotate.cos_theta = cosf(theta);
	rotate.sin_theta = sinf(theta);
	rotate.new_x = rotate.x * rotate.cos_theta - rotate.y * rotate.sin_theta;
	rotate.new_y = rotate.x * rotate.sin_theta + rotate.y * rotate.cos_theta;
	settings->point_of_view->x = rotate.new_x + settings->observer_position->x;
	settings->point_of_view->y = rotate.new_y + settings->observer_position->y;
}
