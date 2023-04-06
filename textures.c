
#include "cub.h"




static int	lookup_color(mlx_texture_t *texture, int x_coord, int y_coord)
{
	int	r;
	int	g;
	int	b;
	int	t;
	int	byte;

	byte = (y_coord * texture->width * 4) + (x_coord * 4);
	r = texture->pixels[byte];
	g = texture->pixels[byte + 1];
	b = texture->pixels[byte + 2];
	t = texture->pixels[byte + 3];
	return (r << 24 | g << 16 | b << 8 | t);
}

void	draw_texture_line(t_settings *settings, mlx_texture_t *texture, float x_shift, int height, int x_image)
{
	int x;
	float y_step;
	int y_image;
	int height_iterations;

	x = (int)(texture->width * x_shift); 

	y_step = (float)texture->height / height;
	y_image = 0;
	if (HEIGHT/2 - height/2 + y_image < 0)
		y_image = - HEIGHT/2 + height/2;
	while (y_image < height && HEIGHT/2 - height/2 + y_image < HEIGHT - 1)
	{
		if (HEIGHT/2 - height/2 + y_image > 0 && HEIGHT/2 - height/2 + y_image < HEIGHT - 1)
			put_pixel(settings, x_image, HEIGHT/2 - height/2 + y_image, lookup_color(texture, x, (int)(y_step * y_image)));
		y_image++;
	}
}

//int	get_texture_color(t_settings *settings, t_render *rend, int y)
//{
//	int	color;
//	int	x_texture;
//	int	y_texture;
//
//	x_texture = (int)round(data->texture->text_xcoord * \
//	(data->texture->current->width - 1));
//	if ((uint32_t)rend->wallheight > data->img->height)
//		y_texture = calc_for_high_wall((double)rend->wallheight, \
//		(double)data->img->height, \
//		(double)data->texture->current->height, (double)y);
//	else
//		y_texture = calc_for_normal_wall(data, rend, y);
//	color = lookup_color(data->texture->current, x_texture, y_texture);
//	return (color);
//}