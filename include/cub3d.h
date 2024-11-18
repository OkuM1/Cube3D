/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:20:48 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/18 15:16:05 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include "../libs/libft/libft.h"
#include "../libs/minilibx-linux/mlx.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include <string.h>

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100

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
    char **map;
    char *N_text;
    char *S_text;
    char *W_text;
    char *E_text;
    int *floor_color;
    int *ceiling_color;
}   t_map;

typedef struct s_player
{
    int player_id;
} t_player;

typedef struct s_game 
{
    t_img img;
    t_map map;
    t_player player;
} t_game;

// Map checker
int	check_input(int ac, char **av);
int	check_datatyp(char *file_name, char *datatype);
int check_map_args(int fd);
int	check_textures(int fd);
int	check_floor(int fd);
int	check_ceiling(int fd);
int	check_RGB_values(char *line, int *i);

// Parser
int parse_file(char **av, t_game *game);

// Hooks
int key_hook(int keycode, t_game *game);
int	refresh_game(t_game *game);


// Exit
int game_exit(t_game *game);

// Error
int error(char *message);



#endif