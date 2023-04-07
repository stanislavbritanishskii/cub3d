/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:37:39 by sbritani          #+#    #+#             */
/*   Updated: 2023/04/07 22:16:50 by dhendzel         ###   ########.fr       */
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

# define HEIGHT			540
# define WIDTH			860
# define VIEW_DIST 3;
# define FORWARD 1
# define BACKWARD 2
# define LEFT 3
# define RIGHT 4
# define SO 4
# define NO 3
# define WE 1
# define EA 2
# define VIEW_POINT_DIST 2
# define MAX_DISTANCE 10
# define STEP_SIZE 0.05f
# define RAY_STEP_SIZE 0.001f
# define TURN_ANGLE 0.03f
# define BIG_DISTANCE 1
# define RANDOM 1000
# define SMALL 0.00001f

typedef struct color_s
{
	int	r;
	int	g;
	int	b;
	int	t;
	int	byte;
	int	res;
}	t_color;

typedef struct texture_s
{
	float	d;
	int		height;
	float	x_shift;
}	t_texture;

typedef struct rotation_s
{
	float	x;
	float	y;
	float	cos_theta;
	float	sin_theta;
	float	new_x;
	float	new_y;
}	t_rotation;

typedef struct march_return_s
{
	float	distance;
	int		direction;
	float	shift;
}	t_march_return;

typedef struct dict_s
{
	char	**keys;
	char	**values;
	int		len;
}	t_dict;

typedef struct s_map
{
	char		**grid;
	int			x_size;
	int			y_size;
	uint32_t	floor;
	uint32_t	ceiling;
}	t_map;

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_settings
{
	uint32_t		floor_color;
	uint32_t		ceiling_color;
	t_dict			*dict;
	t_vector		*observer_position;
	t_vector		*point_of_view;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_map			*map;
}	t_settings;

//functions

//test version
bool			read_map(t_settings *settings, char *path);
//wall checks
int				check_wall_down(float x, float y, t_map *map);
int				check_wall_left(float x, float y, t_map *map);
int				check_wall_right(float x, float y, t_map *map);
int				check_wall_up(float x, float y, t_map *map);
int				get_map_value(int x, int y, t_map *map);
t_vector		get_ray_direction(t_vector observer_position,
					t_vector point_of_view, float angle);
t_march_return	*ray_march(t_vector position, t_vector direction,
					t_map *map, t_march_return *res);
// debug functions
void			print_map(t_map *map, float x, float y, float x2, float y2);
// dict functions;
t_dict			*init_dict(void);
void			dict_add(t_dict *dict, char *key, char *value);
char			*dict_get(t_dict *dict, char *key, char *default_return);
void			dict_delete(t_dict *dict, char *key);
void			free_dict(t_dict *dict);
//draw functions

void			put_pixel(t_settings *settings, int x, int y, uint32_t color);
void			draw_texture_line(t_settings *settings,
					mlx_texture_t *texture, t_texture *info);
// map functions

bool			map_is_closed(t_map *map);
void			clean_map(t_map *map);

#endif