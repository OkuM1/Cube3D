/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:20:48 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/22 17:45:07 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include <string.h>

# define ESC	65307
# define W		119
# define A		97
# define S		115
# define D		100

# define TILE_SIZE 30
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4
# define WIN_WIDTH	800
# define WIN_HEIGHT	600

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
 double		ray_angle;
 double		wall_dist;
 int		wall_flag;		//flag for wall
}	t_ray;

typedef struct s_view
{
	double	x;
	double	y;
	int		height;
	int		width;
	double	zoom;
}	t_view;

typedef struct s_map
{
	char	**map;
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



// Parser
void	save_texture(t_game *game, t_map *map);

// Hooks
int		key_hook(int keycode, t_game *game);
int		refresh_game(t_game *game);

// Exit
int		game_exit(t_game *game);

// Error
int		error(char *message);

#endif
