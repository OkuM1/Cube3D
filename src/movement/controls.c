/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:14:29 by chris             #+#    #+#             */
/*   Updated: 2025/01/17 13:21:45 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move_player(t_game *game, double move_x, double move_y)
{
	int	map_pos_x;
	int	map_pos_y;

	map_pos_x = move_x / TILE_SIZE;
	map_pos_y = move_y / TILE_SIZE;
	if (map_pos_x >= 0 && map_pos_x < game->map.level_width
		&& map_pos_y >= 0 && map_pos_y < game->map.level_height)
	{
		if (game->map.level[map_pos_y][map_pos_x] != '1')
		{
			if (too_close_to_wall(game) == 1 && game->player.u_d == 1)
				return ;
			else
			{
				game->player.x += (move_x - game->player.x);
				game->player.y += (move_y - game->player.y);
			}
		}
	}
	game->player.x_grid = game->player.x / TILE_SIZE;
	game->player.y_grid = game->player.y / TILE_SIZE;
}

void	controls(t_game *game)
{
	double	move_x;
	double	move_y;

	move_x = game->player.x;
	move_y = game->player.y;
	rotate_player(game);
	calc_u_d(game, &move_x, &move_y);
	calc_l_r(game, &move_x, &move_y);
	move_player(game, move_x, move_y);
}
