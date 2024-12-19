/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:20:48 by mokutucu          #+#    #+#             */
/*   Updated: 2024/12/19 17:57:09 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"
//# include "../libs/minilibx-linux/mlx_int.h"
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

# define TILE_SIZE 64

# define ROTATION_SPEED 0.1
# define PLAYER_SPEED 6
# define WIN_WIDTH	800
# define WIN_HEIGHT	600
# define SKY_COLOR 0x87CEEB  // Light blue 
// # define GROUND_COLOR 0x800111  // Red
# define GROUND_COLOR 0x778899	// grey

typedef struct s_img
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
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
	double	ray_angle;
	double	wall_dist;
	// double	hor_x;
	// double	hor_y;
	// double	vert_x;
	// double	vert_y;
	int		wall_flag;
}	t_ray;

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
	int		floor_color[3];
	int		ceiling_color[3];
	char	**level;
	int		level_height;
	int		level_width;
}	t_map;

typedef struct s_player
{
	int		player_id;
	int		x;
	int		y;
	double	player_angle;
	double	move_speed;
	double	rotation_speed;
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
}	t_game;


// Init
void	init_all(t_game *game);

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
int		find_player_start(t_game *game);

// Parser
void	save_texture(t_game *game, t_map *map);

float	nor_angle(float angle);
void	render_wall(t_game *game, int ray);
void	cast_rays(t_game *game);
void	my_mlx_pixel_put(t_game *game, int x, int y, unsigned int color);

// Hooks
int		refresh_game(void *param);
int		handle_keypress(int keycode, void *param);
int		handle_keyrelease(int keycode, void *param);

// Controls
void	controls(t_game *game, double move_x, double move_y);
void	move_player(t_game *game, double move_x, double move_y);
void	rotate_player(t_game *game, int direction);

// Exit
int		game_exit(t_game *game);

// Error
int		error(char *message);
void	debugger(t_game *game, char *struct_name);

#endif
