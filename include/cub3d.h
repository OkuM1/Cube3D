/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:20:48 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/18 19:02:09 by chris            ###   ########.fr       */
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

typedef struct s_img
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*img_address;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_map
{
	char	**map;
	char	*n_text;	//must be lowercase for norminette
	char	*s_text;	//must be lowercase for norminette
	char	*w_text;	//must be lowercase for norminette
	char	*e_text;	//must be lowercase for norminette
	int		floor_color[3];
	int		ceiling_color[3];
	int		map_size;
}	t_map;

typedef struct s_player
{
	int		player_id;
}	t_player;

typedef struct s_game
{
	t_img		img;
	t_map		map;
	t_player	player;
}	t_game;

// Map checker
int		check_input(int ac, char **av, t_game *game, t_map *map);
int		check_datatyp(char *file_name, char *datatype);
int		check_and_save_map_args(char **av, t_game *game, t_map *map);
int		create_file_arr(char **av, t_map *map);
int		open_fd(char **av, int *fd);
int		get_arr_size_and_malloc(int fd, t_map *map);
int		check_and_save_textures(t_game *game, t_map *map);
int		check_and_save_floor(t_map *map);
int		check_and_save_ceiling(t_map *map);
int		check_RGB_values(t_map *map, int *i);

// Parser
int		parse_file(char **av, t_game *game);
void	save_color(t_game *game, t_map *map);
void	save_texture(t_game *game, t_map *map);

// Hooks
int		key_hook(int keycode, t_game *game);
int		refresh_game(t_game *game);

// Exit
int		game_exit(t_game *game);

// Error
int		error(char *message);

#endif
