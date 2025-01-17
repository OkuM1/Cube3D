/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:06:20 by cwick             #+#    #+#             */
/*   Updated: 2025/01/17 13:22:30 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	too_close_to_wall(t_game *game)
{
	if (game->ray.wall_dist < 15)
		return (1);
	return (0);
}

void	rotate_player(t_game *game)
{
	if (game->player.rot == 1)
		game->player.angle += ROTATION_SPEED;
	if (game->player.rot == -1)
		game->player.angle -= ROTATION_SPEED;
	nor_angle(&game->player.angle);
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
}

void	calc_u_d(t_game *game, double *move_x, double *move_y)
{
	if (game->player.u_d == 1)
	{
		*move_x += game->player.dir_x * PLAYER_SPEED;
		*move_y += game->player.dir_y * PLAYER_SPEED;
	}
	if (game->player.u_d == -1)
	{
		*move_x -= game->player.dir_x * PLAYER_SPEED;
		*move_y -= game->player.dir_y * PLAYER_SPEED;
	}
}

void	calc_l_r(t_game *game, double *move_x, double *move_y)
{
	if (game->player.l_r == 1)
	{
		*move_x -= game->player.dir_y * PLAYER_SPEED;
		*move_y += game->player.dir_x * PLAYER_SPEED;
	}
	if (game->player.l_r == -1)
	{
		*move_x += game->player.dir_y * PLAYER_SPEED;
		*move_y -= game->player.dir_x * PLAYER_SPEED;
	}
}
