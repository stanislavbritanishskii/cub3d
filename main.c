/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:54:31 by sbritani          #+#    #+#             */
/*   Updated: 2023/04/05 15:38:21 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

unsigned long createRGBA(char **splitted)
{   
    unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int a;
	
	r = ft_atoi(splitted[0]);
	g = ft_atoi(splitted[1]);
	b = ft_atoi(splitted[2]);
	a = 255;   
	return ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8)
           + (a & 0xff);
}

void	error_exit(t_settings *settings)
{
	if (settings->dict)
		free_dict(settings->dict);
	if (settings->map)
		clean_map(settings->map);
	free(settings);
	ft_putstr_fd("Error\n", 2);
}

t_settings	*init_settings()
{
	t_settings	*res;
	char **splitted;
	
	res = malloc(sizeof(t_settings));
	res->map = NULL;
	res->dict = NULL;

	if (!read_map(res, "map.txt"))
		return (error_exit(res), NULL);
	splitted = ft_split(dict_get(res->dict, "C\0", "hui"), ",");
	res->ceiling_color = createRGBA(splitted);
	ft_split_clear(splitted);
	splitted = ft_split(dict_get(res->dict, "F\0", "hui"), ",");
	res->floor_color = createRGBA(splitted);
	ft_split_clear(splitted);
	res->no = mlx_load_png(dict_get(res->dict, "NO\0", "\0"));
	res->so = mlx_load_png(dict_get(res->dict, "SO\0", "\0"));
	res->ea = mlx_load_png(dict_get(res->dict, "EA\0", "\0"));
	res->we = mlx_load_png(dict_get(res->dict, "WE\0", "\0"));
	res->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	res->image = mlx_new_image(res->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(res->mlx, res->image,0, 0);
//	res->observerPosition = malloc(sizeof(t_vector));
//	res->observerPosition->x = 16.5f;
//	res->observerPosition->y = 2.5f;
//	res->pointOfView = malloc(sizeof(t_vector));
//	res->pointOfView->x = res->observerPosition->x;
//	res->pointOfView->y = res->observerPosition->y + 1.5f + VIEW_POINT_DIST;
	return (res);
}

void	put_pixel(t_settings *settings, int x, int y, uint32_t color)
{
	mlx_put_pixel(settings->image, x, y, color);
}

void rotate_point(t_settings *settings, float theta)
{
	// Translate point to origin
	float x = settings->pointOfView->x - settings->observerPosition->x;
	float y = settings->pointOfView->y - settings->observerPosition->y;

	// Apply rotation matrix
	float cos_theta = cosf(theta);
	float sin_theta = sinf(theta);
	float new_x = x * cos_theta - y * sin_theta;
	float new_y = x * sin_theta + y * cos_theta;

	// Translate point back to original position
	settings->pointOfView->x = new_x + settings->observerPosition->x;
	settings->pointOfView->y = new_y + settings->observerPosition->y;
}

void draw_line(t_settings *settings, int x1, int y1, int x2, int y2, uint32_t color) {
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = x1 < x2 ? 1 : -1;
	int sy = y1 < y2 ? 1 : -1;
	int err = dx - dy;

	while (x1 != x2 || y1 != y2) {
		put_pixel(settings, x1, y1, color);
		int e2 = 2 * err;
		if (e2 > -dy) 
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx) 
		{
			err += dx;
			y1 += sy;
		}
	}
}

void draw_line_floor_sky(t_settings *settings, int x)
{
	int i;
	int color;
	float darkness;
	int	r;
	int	g;
	int	b;
	int	t;

	i = 0;
	while (i < HEIGHT / 2)
	{
		r = settings->ceiling_color >> 24 & 255;
		g = settings->ceiling_color >> 16 & 255;
		b = settings->ceiling_color >> 8 & 255;
		t = settings->ceiling_color & 255;
		darkness = 1 - (((float)RANDOM / ((float)HEIGHT/ 2 - i)) / (float) MAX_DISTANCE);
		if (darkness < 0)
			darkness = 0;
		color = (int)(r * darkness) << 24 | (int)(g * darkness) << 16 | (int)(b * darkness) << 8 | t;
		put_pixel(settings, x, i, color);
		i++;
	}
	while (i < HEIGHT)
	{
		r = settings->floor_color >> 24 & 255;
		g = settings->floor_color >> 16 & 255;
		b = settings->floor_color >> 8 & 255;
		t = settings->floor_color & 255;
		darkness = 1 - (((float)RANDOM / ((float)i - (float)HEIGHT/ 2)) / (float) MAX_DISTANCE);
		if (darkness < 0)
			darkness = 0;
		color = (int)(r * darkness) << 24 | (int)(g * darkness) << 16 | (int)(b * darkness) << 8 | t;
		put_pixel(settings, x, i, color);
		i++;
	}
}

void move(t_settings *settings, float x, float y)
{
//	if (!settings->map->grid[(int) (settings->observerPosition->x + x)][(int) (settings->observerPosition->y + y)]) {
//		settings->observerPosition->x += x;
//		settings->observerPosition->y += y;
//		settings->pointOfView->x += x;
//		settings->pointOfView->y += y;
//	}
	if (settings->map->grid[(int) (settings->observerPosition->y)][(int) (settings->observerPosition->x + x)] == '0') 
	{
		settings->observerPosition->x += x;
		settings->pointOfView->x += x;
		if (settings->map->grid[(int) (settings->observerPosition->y + y)][(int) (settings->observerPosition->x)] =='0') 
		{
			settings->observerPosition->y += y;
			settings->pointOfView->y += y;
		}
	}
	else if (settings->map->grid[(int) (settings->observerPosition->y + y)][(int) (settings->observerPosition->x)] == '0') 
	{
		settings->observerPosition->y += y;
		settings->pointOfView->y += y;
		if (settings->map->grid[(int) (settings->observerPosition->y)][(int) (settings->observerPosition->x + x)] == '0') 
		{
			settings->observerPosition->x += x;
			settings->pointOfView->x += x;
		}
	}
}


float min(float a, float b)
{
	if (a < b)
		return a;
	return b;
}

void move_character(t_settings *settings, float move_dir) {
	// Calculate unit vector in the view direction
	float d_x = settings->pointOfView->x - settings->observerPosition->x;
	float d_y = settings->pointOfView->y - settings->observerPosition->y;
	float delta = STEP_SIZE;
	d_x *= delta;
	d_y *= delta;
	if (move_dir == FORWARD)
	{
		move(settings, d_x, d_y);
	}
	else if (move_dir == BACKWARD)
	{
		move(settings, -d_x, -d_y);
	}
	else if (move_dir == LEFT)
	{
		move(settings, d_y, -d_x);
	}
	else if (move_dir == RIGHT)
	{
		move(settings, -d_y, d_x);
	}
}

float vector_dot(t_vector v1, t_vector v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

void	draw_walls(t_settings *settings)
{
	float		f;
	float		d;
	float		angle;
	float		distance;
	t_vector	direction;
	t_march_return march;

//	f = -WIDTH / (M_PI);
	f = -1 / (FOV_1);
	d = WIDTH;
	angle = -FOV_HALF;
//	while (angle < FOV_HALF)
	while (d >= 0)
	{

		direction = getRayDirection(*settings->observerPosition, *settings->pointOfView, angle);
		rayMarch(*settings->observerPosition, direction, settings->map, &march);
		march.distance *= cosf(angle);
		if (march.direction == SO)
		{
			draw_texture_line(settings, settings->so, march.shift, RANDOM / (march.distance + 0.00001f),
							  d);
		}
		if (march.direction == EA)
		{
			draw_texture_line(settings, settings->ea, march.shift, RANDOM / (march.distance + 0.00001f),
							  d);
		}
		if (march.direction == NO)
		{
			draw_texture_line(settings, settings->no, march.shift, RANDOM / (march.distance + 0.00001f),
							  d);
		}
		if (march.direction == WE)
		{
			draw_texture_line(settings, settings->we, march.shift, RANDOM / (march.distance + 0.00001f),
							  d);
		}
		if(march.direction == 5)
			draw_line_floor_sky(settings, d);
		d = d - 1;
		angle += FOV_1 / WIDTH;


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

void ft_hook(void* param)
{
	t_settings* settings = param;

	print_map(settings->map, settings->observerPosition->x, settings->observerPosition->y, settings->pointOfView->x, settings->pointOfView->y);
	draw_sky_floor(settings, false);
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
	if (mlx_is_key_down(settings->mlx, MLX_KEY_E))
		rotate_point(settings, TURN_ANGLE);
	if (mlx_is_key_down(settings->mlx, MLX_KEY_Q))
		rotate_point(settings, -TURN_ANGLE);
	if (mlx_is_key_down(settings->mlx, MLX_KEY_Z))
	{	settings->pointOfView->y = settings->observerPosition->y + VIEW_POINT_DIST;
		settings->pointOfView->x = settings->observerPosition->x;}
	draw_walls(settings);
	usleep(10000);
}

 void autopilot(void *param)
 {
 	t_settings* settings = param;
	 t_march_return march;

 	print_map(settings->map, settings->observerPosition->x, settings->observerPosition->y, settings->pointOfView->x, settings->pointOfView->y);
	 draw_sky_floor(settings, false);

 	float angle = -0.5f * M_PI;
 	t_vector direction = getRayDirection(*settings->observerPosition, *settings->pointOfView, angle);
 	rayMarch(*settings->observerPosition, direction, settings->map, &march);
	float distance = march.distance;
 	angle = 0;
 	direction = getRayDirection(*settings->observerPosition, *settings->pointOfView, angle);
 	rayMarch(*settings->observerPosition, direction, settings->map, &march);
	float distance2 = march.distance;
 	angle = 0.5f * M_PI;
 	direction = getRayDirection(*settings->observerPosition, *settings->pointOfView, angle);
 	rayMarch(*settings->observerPosition, direction, settings->map, &march);
	float distance3 = march.distance;
 	if (distance3 + distance + distance2 < 1) {
		rotate_point(settings, 0.06f);
		move_character(settings, BACKWARD);
	}
 	else if (distance > distance2 && distance > distance3)
 		rotate_point(settings, 0.02f);
 	else if (distance3 > distance2 && distance3 > distance)
 		rotate_point(settings, -0.02f);
//	 if (distance2 > 0.5f)
	move_character(settings, FORWARD);
	 draw_walls(settings);
 }

//void draw_minimap(t_settings *settings, )

void	check_leaks(void)
{
	system("leaks cub3d");
}

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
}

int main(int argc, char **argv)
{

	t_settings *settings = init_settings();

	atexit(check_leaks);
	if(settings)
	{
//		 print_map(settings->map, settings->observerPosition->x, settings->observerPosition->y, settings->pointOfView->x, settings->pointOfView->y);

		draw_sky_floor(settings, true);
		mlx_loop_hook(settings->mlx, autopilot, settings);
		mlx_loop(settings->mlx);
		clean_settings(settings);
		return (0);
	}
	return (1);
}