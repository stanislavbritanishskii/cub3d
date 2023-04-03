/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:54:31 by sbritani          #+#    #+#             */
/*   Updated: 2023/03/06 10:30:19 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_settings	*init_settings()
{
	t_settings	*res;

	res = malloc(sizeof(t_settings));
	res->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	res->image = mlx_new_image(res->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(res->mlx, res->image,0, 0);
	res->map = read_map(res, "sosi\0");
	res->observerPosition = malloc(sizeof(t_vector));
	res->observerPosition->x = 1.5f;
	res->observerPosition->y = 1.5f;
	res->pointOfView = malloc(sizeof(t_vector));
	res->pointOfView->x = 1.5f;
	res->pointOfView->y = res->observerPosition->y + 1.5f + VIEW_POINT_DIST;
	return (res);
}

void	put_pixel(t_settings *settings, int x, int y, uint32_t color)
{
	mlx_put_pixel(settings->image, x, y, color);
}

void rotate_point(t_settings *settings, float theta) {
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
		if (e2 > -dy) {
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y1 += sy;
		}
	}
}

void move(t_settings *settings, float x, float y)
{
	if (!settings->map->grid[(int) (settings->observerPosition->x + x)][(int) (settings->observerPosition->y + y)]) {
		settings->observerPosition->x += x;
		settings->observerPosition->y += y;
		settings->pointOfView->x += x;
		settings->pointOfView->y += y;
	}
	else if (!settings->map->grid[(int) (settings->observerPosition->x + x)][(int) (settings->observerPosition->y)]) {
		settings->observerPosition->x += x;
		settings->pointOfView->x += x;
	}
	else if (!settings->map->grid[(int) (settings->observerPosition->x)][(int) (settings->observerPosition->y + y)]) {
		settings->observerPosition->y += y;
		settings->pointOfView->y += y;
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

	float delta = STEP_SIZE / VIEW_POINT_DIST;
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

void ft_hook(void* param)
{
	t_settings* settings = param;

	print_map(settings->map, settings->observerPosition->x, settings->observerPosition->y, settings->pointOfView->x, settings->pointOfView->y);
	float f = -WIDTH / (500 * M_PI);
	float d = WIDTH;
	for (float angle = -0.25f * M_PI; angle < 0.25f * M_PI; angle += 0.001f) {
		t_vector direction = getRayDirection(*settings->observerPosition, *settings->pointOfView, angle);
		float distance = rayMarch(*settings->observerPosition, direction, settings->map);
//		distance /= cosf(angle / M_PI);
//		printf("Angle: %f, Distance: %f\n", angle, distance);
		draw_line(settings, d, HEIGHT / 2 - min(100 / (distance + 0.00001f), HEIGHT / 2 - 2), d, HEIGHT / 2 + min(100 / (distance + 0.00001f), HEIGHT / 2 - 2), 0x00000000);
		d = d + f;
	}
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
		rotate_point(settings, 0.05f);
	if (mlx_is_key_down(settings->mlx, MLX_KEY_Q))
		rotate_point(settings, -0.05f);
	if (mlx_is_key_down(settings->mlx, MLX_KEY_Z))
	{	settings->pointOfView->y = settings->observerPosition->y + VIEW_POINT_DIST;
		settings->pointOfView->x = settings->observerPosition->x;}


	f = -WIDTH / (500 * M_PI);
	d = WIDTH;



//	for (float angle = -FOV / 2.0f; angle < FOV / 2.0f; angle += FOV / WIDTH) {
//		t_vector direction = getRayDirection(*settings->observerPosition, *settings->pointOfView, angle);
//		t_vector playerDirection;
//		playerDirection.x = settings->pointOfView->x - settings->observerPosition->x;
//		playerDirection.y = settings->pointOfView->y - settings->observerPosition->y;
//		float distance = rayMarch(*settings->observerPosition, direction, settings->map);
//		float dotProduct = vector_dot(direction, playerDirection);
//		float rayAngle = acosf(dotProduct);
//		distance = distance * cosf(rayAngle);
//		float scalingFactor = WIDTH / (2.0f * tanf(FOV / 2.0f));
//		float wallHeight = HEIGHT / distance * scalingFactor;
//		int wallTop = (HEIGHT - wallHeight) / 2.0f;
//		int wallBottom = wallTop + wallHeight;
//		draw_line(settings, d, wallTop, d, wallBottom, 0xFFFFFFFF);
//		d += f;
//	}

	for (float angle = -0.25f * M_PI; angle < 0.25f * M_PI; angle += 0.001f) {
		t_vector direction = getRayDirection(*settings->observerPosition, *settings->pointOfView, angle);
		float distance = rayMarch(*settings->observerPosition, direction, settings->map);
		draw_line(settings, d, HEIGHT / 2 - min(100 / (distance + 0.00001f), HEIGHT / 2 - 2), d, HEIGHT / 2 + min(100 / (distance + 0.00001f), HEIGHT / 2 - 2), 0xFFFFF);
		d = d + f;
	}
}
//		float scalingFactor = (WIDTH / 2.0f) / tanf(90.0f / 2.0f);
//		printf("Angle: %f, Distance: %f\n", angle, distance);
//		float scalingFactor = (WIDTH / 2.0f) / tanf(90.0f / 2.0f);
//		distance /= cosf(angle / M_PI);

void looper(void *param)
{
	t_settings *settings = param;
	float f = WIDTH / (500 * M_PI);
	float d = f;
	for (float angle = -0.25f * M_PI; angle < 0.25f * M_PI; angle += 0.001f) {
		t_vector direction = getRayDirection(*settings->observerPosition, *settings->pointOfView, angle);
		float distance = rayMarch(*settings->observerPosition, direction, settings->map);
		printf("Angle: %f, Distance: %f\n", angle, distance);
		draw_line(settings, d, HEIGHT / 2 - distance * 50, d, HEIGHT / 2 + distance * 50, 0xFFFFFFFF);
		d = d + f;
	}
}



//void draw_minimap(t_settings *settings, )

int main(int argc, char **argv)
{

	t_settings *settings = init_settings();
	print_map(settings->map, settings->observerPosition->x, settings->observerPosition->y, settings->pointOfView->x, settings->pointOfView->y);
	float f = WIDTH / (500 * M_PI);
	float d = f;
//	for (float angle = -0.25f * M_PI; angle < 0.25f * M_PI; angle += 0.001f) {
//		t_vector direction = getRayDirection(*settings->observerPosition, *settings->pointOfView, angle);
//		float distance = rayMarch(*settings->observerPosition, direction, settings->map);
//		printf("Angle: %f, Distance: %f\n", angle, distance);
//		draw_line(settings, d, HEIGHT / 2 - distance * 50, d, HEIGHT / 2 + distance * 50, 0xFFFFFFFF);
//		d = d + f;
//	}

	mlx_loop_hook(settings->mlx, ft_hook, settings);

	mlx_loop(settings->mlx);

}


