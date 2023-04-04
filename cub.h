/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:37:39 by sbritani          #+#    #+#             */
/*   Updated: 2023/04/04 23:03:44 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include "libs/libft/libft.h"
# include "libs/MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# define RED 0xFF0000FF
# define BLUE 0x0000FFFF
# define GREEN 0x00FF00FF
# define WHITE 0xFFFFFFFF
# define BLACK 0x00000000
# define HEIGHT			1080
# define WIDTH			1920

# define VIEW_DIST 3;

#define FORWARD 1
#define BACKWARD 2
#define LEFT 3
#define RIGHT 4
# define VIEW_POINT_DIST 2
# define MAX_DISTANCE 20
# define STEP_SIZE 0.01f
# define RAY_STEP_SIZE 0.001f
# define TURN_ANGLE 0.03f
# define BIG_DISTANCE 1
# define SKY 0x8080DFFF
# define FLOOR 0xBDA045FF
# define FOV 60.0f // in degrees
# define CELL 32
# define SPEED 16

typedef struct dict_s
{
	char	**keys;
	char	**values;
	int		len;
}	t_dict;

typedef struct s_map
{
	char	**grid;
	int	x_size;
	int y_size;
	uint32_t floor;
	uint32_t ceiling;
}   t_map;

typedef struct s_vector
{
	float x;
	float y;
} t_vector;

typedef struct s_settings
{
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	t_dict		*dict;
	t_vector	*observerPosition;
	t_vector	*pointOfView;
	mlx_texture_t *no;
	mlx_texture_t *so;
	mlx_texture_t *we;
	mlx_texture_t *ea;
	mlx_t		*mlx;
	mlx_image_t	*image;

	t_map	*map;
}       t_settings;




//functions

//test version
bool read_map(t_settings* settings, char *path);


//wall checks
int	check_wall_down(float x, float y, t_map *map);
int	check_wall_left(float x, float y, t_map *map);
int	check_wall_right(float x, float y, t_map *map);
int	check_wall_up(float x, float y, t_map *map);


//
int getMapValue(int x, int y, t_map *map);
t_vector getRayDirection(t_vector observerPosition, t_vector pointOfView, float angle);
float rayMarch(t_vector position, t_vector direction, t_map *map);

// debug functions
void	print_map(t_map *map, float x, float y, float x2, float y2);

// dict functions;
t_dict	*init_dict(void);
void	dict_add(t_dict *dict, char *key, char *value);
char	*dict_get(t_dict *dict, char *key, char *default_return);
void	dict_delete(t_dict *dict, char *key);
void	free_dict(t_dict *dict);
//draw functions

void	put_pixel(t_settings *settings, int x, int y, uint32_t color);
void	draw_texture_line(t_settings *settings, mlx_texture_t *texture, float x_shift, int height, int x_image);

// map functions

bool map_is_closed(t_map *map);


#endif