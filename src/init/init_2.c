/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:44:42 by cwick             #+#    #+#             */
/*   Updated: 2025/01/17 14:17:28 by cwick            ###   ########.fr       */
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
	game->ray.h_inter = 0;
	game->ray.v_inter = 0;
	game->ray.wall_dist = 0;
	game->ray.wall_side = 0;
	game->ray.wall_heigt = 0;
	game->ray.hor_x_map = 0;
	game->ray.hor_y_map = 0;
	game->ray.vert_x_map = 0;
	game->ray.vert_y_map = 0;
	game->ray.step_x = 0;
	game->ray.step_y = 0;
	game->ray.wall_hit_x = 0;
}
