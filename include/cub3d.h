/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:20:48 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/22 15:47:06 by mokutucu         ###   ########.fr       */
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
# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080

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
}	t_img;

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
	char	*n_text;	//must be lowercase for norminette
	char	*s_text;	//must be lowercase for norminette
	char	*w_text;	//must be lowercase for norminette
	char	*e_text;	//must be lowercase for norminette
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
