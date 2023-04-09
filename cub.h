/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:37:39 by sbritani          #+#    #+#             */
/*   Updated: 2023/04/09 17:10:08 by dhendzel         ###   ########.fr       */
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
# include <sys/time.h> 

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
# define MAX_DISTANCE 5
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
	mlx_texture_t	*screame;
	mlx_image_t		*screamer;
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_map			*map;
	int				counter;
	int				max_counter;
}	t_settings;

//functions

//init.c
void			null_all(t_settings *res);
t_settings		*init_settings(char *path);
void			error_exit(t_settings *settings);

//color.c
unsigned long	create_rgba(char **splitted, bool *check);
bool			create_color(t_settings *res, char key);
int				get_color(uint32_t color, float darkness);
int				splitted_len(char **splitted);

//draw_wall.c
void			draw_walls(t_settings *settings);
void			draw_direction(t_settings *settings,
					t_march_return *march, float d);
void			draw_sky_floor(t_settings *settings, bool start);
void			draw_line_floor_sky(t_settings *settings, int x);
void			put_pixel(t_settings *settings, int x, int y, uint32_t color);

//move_rotate.c
void			move(t_settings *settings, float x, float y);
void			move_character(t_settings *settings, float move_dir);
void			rotate_point(t_settings *settings, float theta);
void			reset_view(t_settings *settings);

//clean.c
void			clean_settings(t_settings *settings);
void			clean_map(t_map *map);
void			free_vectors(t_settings *settings);
//checks.c
int				map_extension_correct(char *map_path);
bool			is_player(char element);
bool			wrong_char(char element);
bool			check_dict_filled(t_dict *dict);
bool			check_final_map(t_map *map, t_settings *settings);

//create_map.c
t_map			*create_final_map(char **i_map);
char			**create_initial_map(int fd);
void			get_max_width(t_map *res, int *height, char **i_map);

//read_map.c
void			set_player(t_settings *settings, t_map *map, int x, int y);
bool			read_map(t_settings *settings, char *path);
bool			initial_parsing(t_dict *dict, char *path, int fd);
bool			add_to_dict(char *str, t_dict *dict);
void			read_map_error(char *str, t_dict *dict);

//math_utils.c
float			distance_to_grid(float a);
float			abs_float(float a);
float			min(float a, float b);
int				get_map_value(int x, int y, t_map *map);

//map_check.c
bool			dfs(t_map *map, int x, int y);
bool			map_is_closed(t_map *map);
void			find_player(t_map *map, t_map *local, int *x, int *y);
t_map			*copy_map(t_map *orig);

//utils.c
t_march_return	*ray_march(t_vector position, t_vector direction,
					t_map *map, t_march_return *res);
void			hit_a_wall(t_vector position, t_vector direction,
					t_map *map, t_march_return *res);
bool			incredible_check(t_vector position, t_vector direction,
					t_map *map, t_march_return *res);
t_vector		get_ray_direction(t_vector observer_position,
					t_vector point_of_view, float angle);
void			print_map(t_map *map, t_vector *player, t_vector *view);

// dict.c;
t_dict			*init_dict(void);
void			dict_add(t_dict *dict, char *key, char *value);
char			*dict_get(t_dict *dict, char *key, char *default_return);
void			dict_delete(t_dict *dict, char *key);
void			free_dict(t_dict *dict);

//textures.c
int				lookup_color(mlx_texture_t *texture,
					int x_coord, int y_coord, float darkness);
void			draw_texture_line(t_settings *settings,
					mlx_texture_t *texture, t_texture *info);

//main.c
void			check_music(t_settings *settings);
void			ft_hook(void *param);

#endif
