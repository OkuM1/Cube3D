/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:32:57 by mokutucu          #+#    #+#             */
/*   Updated: 2024/12/10 16:04:55 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void init_mlx(t_game *game)
{
	game->img.mlx = NULL;
	game->img.mlx_win = NULL;
	game->img.img = NULL;
	game->img.img_address = NULL;
	game->img.bpp = 0;
	game->img.line_length = 0;
	game->img.endian = 0;
}

void init_game(t_game *game)
{
	game->map.file = NULL;
	game->map.n_text = NULL;
	game->map.s_text = NULL;
	game->map.w_text = NULL;
	game->map.e_text = NULL;
	game->map.floor_color[0] = -1;
	game->map.floor_color[1] = -1;
	game->map.floor_color[2] = -1;
	game->map.ceiling_color[0] = -1;
	game->map.ceiling_color[1] = -1;
	game->map.ceiling_color[2] = -1;
	game->map.map_size = 0;
	game->map.level = NULL;
	game->map.level_height = 0;
	game->map.level_width = 0;
}

void	init_all(t_game *game)
{
	init_game(game);
	init_mlx(game);
	game->view.fov = 60 * (M_PI / 180.0);
}