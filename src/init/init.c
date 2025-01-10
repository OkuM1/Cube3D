/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:32:57 by mokutucu          #+#    #+#             */
/*   Updated: 2025/01/10 14:31:19 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_texture(t_game *game)
{
	game->tex.y = 0;
	game->tex.x = 0;
	game->tex.bpp = 0;
	game->tex.line_length = 0;
	game->tex.endian = 0;
	game->tex.color = 0;
	game->tex.addr = NULL;
	game->tex.pixel = NULL;
	game->tex.texture = NULL;
}

void	init_ray(t_game *game)
{
	game->ray.angle = 0;
	game->ray.delta_x = 0;
	game->ray.delta_y = 0;
	game->ray.dir_x = 0;
	game->ray.dir_y = 0;
	game->ray.hor_x = 0;
	game->ray.hor_y = 0;
	game->ray.vert_x = 0;
	game->ray.vert_y = 0;
	game->ray.plane_x = 0;
	game->ray.plane_y = 0;
	game->ray.wall_dist = 0;
	game->ray.wall_side = 0;
	game->ray.wall_heigt = 0;
	game->ray.hor_x_map = 0;
	game->ray.hor_y_map = 0;
	game->ray.vert_x_map = 0;
	game->ray.vert_y_map = 0;
	game->ray.step_x = 0;
	game->ray.step_y = 0;
}

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