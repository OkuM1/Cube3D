/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:20:48 by mokutucu          #+#    #+#             */
/*   Updated: 2025/01/17 14:21:43 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include <string.h>
# include <math.h>

# define ESC		65307
# define W			119
# define A			97
# define S			115
# define D			100
# define L_ARROW	65361
# define R_ARROW	65363
# define SHIFT		16

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define TILE_SIZE		64
# define TILE_SIZE_MM	16

# define ROTATION_SPEED 0.01
# define PLAYER_SPEED 1
# define WIN_WIDTH	800
# define WIN_HEIGHT	600
# define PLAYER_COLOR 0x5cf700

typedef struct s_img
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	void	*textures[4];
	int		tex_width;
	int		tex_height; 
	char	*img_address;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	char	*n_texture_add;
	char	*s_texture_add;
	char	*w_texture_add;
	char	*e_texture_add;
}	t_img;

typedef struct s_ray
{
	double	angle;
	double	wall_dist;
	double	hor_x;
	double	hor_y;
	double	vert_x;
	double	vert_y;
	double	dir_x;
	double	dir_y;
	double	h_inter;
	double	v_inter;
	int		delta_x;
	int		delta_y;
	int		hor_x_map;
	int		hor_y_map;
	int		vert_x_map;
	int		vert_y_map;
	double	step_x;
	double	step_y;
	char	wall_side;
	double	wall_heigt;
	double	wall_hit_x;
	int		hit_side;
}	t_ray;

typedef struct s_texture
{
	int		y;
	int		x;
	int		bpp;
	int		line_length;
	int		endian;
	int		color;
	char	*addr;
	char	*pixel;
	void	*texture;
}	t_texture;

typedef struct s_view
{
	double	fov;
	double	x;
	double	y;
	int		height;
	int		width;
	double	zoom;
}	t_view;

typedef struct s_map
{
	char	**file;
	int		map_size;
	char	*n_text;
	char	*s_text;
	char	*w_text;
	char	*e_text;
	int		floor_color;
	int		ceiling_color;
	char	**level;
	int		level_height;
	int		level_width;
}	t_map;

typedef struct s_player
{
	int		player_id;
	double	x;
	double	y;
	double	angle;
	double	dir_x;
	double	dir_y;
	int		x_grid;
	int		y_grid;
	int		l_r;
	int		u_d;
	int		rot;
}	t_player;

typedef struct s_game
{
	t_view		view;
	t_img		img;
	t_map		map;
	t_player	player;
	t_ray		ray;
	t_texture	tex;
}	t_game;

// Init
void	init_all(t_game *game);
void	init_view(t_game *game);
void	init_map(t_game *game);
void	init_img(t_game *game);
void	init_player(t_game *game);
void	init_ray(t_game *game);
void	init_texture(t_game *game);

// Map checker
int		check_input(int ac, char **av, t_game *game);
int		check_datatyp(char *file_name, char *datatype);
int		check_and_save_map_args(char **av, t_game *game);
int		create_file_arr(char **av, t_map *map);
int		open_fd(char **av, int *fd);
int		get_arr_size_and_malloc(int fd, t_map *map);
int		check_and_save_textures(t_game *game, t_map *map);
int		check_and_save_color(t_game *game, t_map *map, char identifier);
int		check_and_save_level(t_map *map);
int		find_level_start(char **map);
int		find_level_end(char **map);
int		is_level_line(char *line);
int		find_player_start(t_game *game);
int		rgba_int(int r, int g, int b, int a);
char	*remove_newline(char *string);
int		space_counter(char *str);
void	free_array(char **arr);
int		rgba_int(int r, int g, int b, int a);

// Raycaster
void	save_texture(t_game *game, t_map *map);
void	create_image(t_game *game);
void	cast_rays(t_game *game);
double	get_v_inter(t_game *game);
double	get_h_inter(t_game *game);
int		check_wall_hit(t_game *game, char c, double ray_y, double ray_x);
int		control_wall_hit(t_game *game, int map_x, int map_y);
int		check_boundaries(t_game *game, char c);
void	nor_angle(double *angle);
double	deg_to_rad(double a);
void	clear_image(t_game *game);
void	render_wall(t_game *game, int ray);
void	check_wall_dir(t_game *game, double h_inter, double v_inter);
void	draw_wall(t_game *game, int ray, int top_pix, int bottom_pix);
void	draw_logic(t_game *game, double *tex_pos, double *tex_step);
void	load_textures(t_game *game);
void	texture_wall_hit(t_game *game);
void	*get_texture(t_game *game);
void	draw_sky(t_game *game, int ray, int top_pix);
void	draw_ground(t_game *game, int ray, int bottom_pix);
void	my_mlx_pixel_put(t_game *game, int x, int y, unsigned int color);

// Hooks
int		refresh_game(void *param);
int		handle_keypress(int keycode, void *param);
int		handle_keyrelease(int keycode, void *param);

// Controls
void	controls(t_game *game);
void	move_player(t_game *game, double move_x, double move_y);
void	rotate_player(t_game *game);
void	calc_u_d(t_game *game, double *move_x, double *move_y);
void	calc_l_r(t_game *game, double *move_x, double *move_y);
int		too_close_to_wall(t_game *game);

// Exit
int		game_exit(t_game *game);

// Error
int		error(char *message);
void	debugger(t_game *game, char *struct_name);
void	print_player(t_game *game);
void	print_map(t_game *game);
void	print_view(t_game *game);
void	print_ray(t_game *game);
void	print_img(t_game *game);

// Bonus Minimap
void	create_minimap(t_game *game);
void	draw_map2d(t_game *game);
void	draw_rectangle(t_game *game, int x_len, int y_len, unsigned int color);
void	draw_player(t_game *game);
void	draw_player_direction(t_game *game);
void	draw_line(t_game *game, int end_x, int end_y, int color);

#endif