/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:32:57 by mokutucu          #+#    #+#             */
/*   Updated: 2024/12/19 12:31:38 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_player(t_game *game)
{
	game->player.x = game->view.x * TILE_SIZE + TILE_SIZE / 2;
	game->player.y = game->view.y * TILE_SIZE + TILE_SIZE / 2;
	game->view.fov = (60 * M_PI) / 180.0;
	game->player.player_angle = 0;
}

void	init_mlx(t_game *game)
{
	game->img.mlx = NULL;
	game->img.mlx_win = NULL;
	game->img.img = NULL;
	game->img.img_address = NULL;
	game->img.bpp = 0;
	game->img.line_length = 0;
	game->img.endian = 0;
}

void	init_game(t_game *game)
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

void    init_view(t_game *game)
{
    game->view.x = 0;
    game->view.y = 0;
    game->view.height = WIN_HEIGHT;
    game->view.width = WIN_WIDTH;
    game->view.zoom = 1.0;
}


void	init_all(t_game *game)
{
	init_view(game);
	init_game(game);
	init_mlx(game);
	init_player(game);
}