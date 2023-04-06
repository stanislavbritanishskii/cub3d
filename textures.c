
#include "cub.h"




static int	lookup_color(mlx_texture_t *texture, int x_coord, int y_coord, float darkness)
{
	int	r;
	int	g;
	int	b;
	int	t;
	int	byte;
	int res;

	byte = (y_coord * texture->width * 4) + (x_coord * 4);
	r = texture->pixels[byte];
	g = texture->pixels[byte + 1];
	b = texture->pixels[byte + 2];
	t = texture->pixels[byte + 3];
	res = (int)(r * darkness) << 24 | (int)(g * darkness) << 16 | (int)(b * darkness) << 8 | t;
//	return (r << 24 | g << 16 | b << 8 | t);
	return res;
}

void	draw_texture_line(t_settings *settings, mlx_texture_t *texture, float x_shift, int height, int x_image)
{
	int x;
	float y_step;
	int y_image;
	float darkness;

	x = (int)(texture->width * x_shift); 
	darkness = 1 - (((float)RANDOM / height) / (float) MAX_DISTANCE);
	y_step = (float)texture->height / height;
	y_image = 0;
	if (HEIGHT/2 - height/2 + y_image < 0)
		y_image = - HEIGHT/2 + height/2;
	while (y_image < height && HEIGHT/2 - height/2 + y_image < HEIGHT)
	{
		if (HEIGHT/2 - height/2 + y_image >= 0 && HEIGHT/2 - height/2 + y_image < HEIGHT)
			put_pixel(settings, x_image, HEIGHT/2 - height/2 + y_image, lookup_color(texture, x, (int)(y_step * y_image), darkness));
		y_image++;
	}
}
