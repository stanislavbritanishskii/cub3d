/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:42:31 by dhendzel          #+#    #+#             */
/*   Updated: 2023/04/09 16:31:19 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	lookup_color(mlx_texture_t *texture,
		int x_coord, int y_coord, float darkness)
{
	t_color	color;

	color.byte = (y_coord * texture->width * 4) + (x_coord * 4);
	color.r = texture->pixels[color.byte];
	color.g = texture->pixels[color.byte + 1];
	color.b = texture->pixels[color.byte + 2];
	color.t = texture->pixels[color.byte + 3];
	color.res = (int)(color.r * darkness) << 24
		| (int)(color.g * darkness) << 16
		| (int)(color.b * darkness) << 8 | color.t;
	return (color.res);
}

void	draw_texture_line(t_settings *settings,
	mlx_texture_t *texture, t_texture *info)
{
	int		x;
	float	y_step;
	int		y_image;
	float	darkness;

	x = (int)(texture->width * info->x_shift);
	darkness = 1 - (((float)RANDOM / info->height) / (float) MAX_DISTANCE);
	y_step = (float)texture->height / info->height;
	y_image = 0;
	if (HEIGHT / 2 - info->height / 2 + y_image < 0)
		y_image = -HEIGHT / 2 + info->height / 2;
	while (y_image < info->height && HEIGHT
		/ 2 - info->height / 2 + y_image < HEIGHT)
	{
		if (HEIGHT / 2 - info->height / 2 + y_image >= 0
			&& HEIGHT / 2 - info->height / 2 + y_image < HEIGHT)
			put_pixel(settings, info->d,
				HEIGHT / 2 - info->height / 2 + y_image,
				lookup_color(texture, x, (int)(y_step * y_image), darkness));
		y_image++;
	}
}
