/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:32:57 by mokutucu          #+#    #+#             */
/*   Updated: 2025/01/17 13:48:47 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_player(t_game *game)
{
	game->player.x = 0;
	game->player.y = 0;
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	game->player.x_grid = 0;
	game->player.y_grid = 0;
	game->player.angle = 0;
	game->player.l_r = 0;
	game->player.u_d = 0;
	game->player.rot = 0;
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
	game->map.floor_color = 0;
	game->map.ceiling_color = 0;
	game->map.map_size = 0;
	game->map.level = NULL;
	game->map.level_height = 0;
	game->map.level_width = 0;
}

void	init_view(t_game *game)
{
	game->view.fov = M_PI / 3;
	game->view.x = WIN_WIDTH / 2;
	game->view.y = WIN_HEIGHT / 2;
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
	init_ray(game);
}
