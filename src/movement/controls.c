/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:14:29 by chris             #+#    #+#             */
/*   Updated: 2024/12/19 15:40:44 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	rotate_player(t_game *game, int direction)
{
	if (direction == 1)		//rotate right
	{
		game->player.player_angle += ROTATION_SPEED;
		if (game->player.player_angle > 2 * M_PI)
			game->player.player_angle -= 2 * M_PI;
	}
	else					//rotate left
	{
		game->player.player_angle -= ROTATION_SPEED;
		if (game->player.player_angle < 0)
			game->player.player_angle += 2 * M_PI;
	}
}

void	move_player(t_game *game, double move_x, double move_y)
{
	int	new_x;
	int	new_y;
	int	map_pos_x;
	int	map_pos_y;

	new_x = game->player.x + move_x;
	new_y = game->player.y + move_y;
	map_pos_x = new_x / TILE_SIZE;
	map_pos_y = new_y / TILE_SIZE;
	if (game->map.level[map_pos_y][map_pos_x] != '1' &&
		game->map.level[map_pos_y][game->player.x / TILE_SIZE] != '1' &&
		game->map.level[game->player.y / TILE_SIZE][map_pos_x] != '1')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	controls(t_game *game, double move_x, double move_y)
{
	if (game->player.rot == 1) //rotate right
		rotate_player(game, 1);
	if (game->player.rot == -1) //rotate left
		rotate_player(game, 0);
	if (game->player.l_r == 1) //move right
	{
		move_x = -sin(game->player.player_angle) * PLAYER_SPEED;
		move_y = cos(game->player.player_angle) * PLAYER_SPEED;
	}
	if (game->player.l_r == -1) //move left
	{
		move_x = sin(game->player.player_angle) * PLAYER_SPEED;
		move_y = -cos(game->player.player_angle) * PLAYER_SPEED;
	}
	if (game->player.u_d == 1) //move up
	{
		move_x = cos(game->player.player_angle) * PLAYER_SPEED;
		move_y = sin(game->player.player_angle) * PLAYER_SPEED;
	}
	if (game->player.u_d == -1) //move down
	{
		move_x = -cos(game->player.player_angle) * PLAYER_SPEED;
		move_y = -sin(game->player.player_angle) * PLAYER_SPEED;
	}
	move_player(game, move_x, move_y); // move the player
}
