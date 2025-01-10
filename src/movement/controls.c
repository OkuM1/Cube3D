/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:14:29 by chris             #+#    #+#             */
/*   Updated: 2025/01/10 15:18:33 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	rotate_player(t_game *game, int direction)
{
	if (direction == 1)		//rotate right
		game->player.angle += ROTATION_SPEED;
	if (direction == -1)	// rotate left
		game->player.angle -= ROTATION_SPEED;
	nor_angle(&game->player.angle);
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
}

int	too_close_to_wall(t_game *game)
{
	if (game->ray.wall_dist < 15)
		return (1);
	return (0);
}

void	move_player(t_game *game, double move_x, double move_y)
{
	int	map_pos_x;
	int	map_pos_y;

	map_pos_x = move_x / TILE_SIZE;
	map_pos_y = move_y / TILE_SIZE;
	if (map_pos_x >= 0 && map_pos_x < game->map.level_width
		&& map_pos_y >= 0 && map_pos_y < game->map.level_height)
	{
		if (game->map.level[map_pos_y][map_pos_x] != '1') // Wall collision
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
	debugger(game, "player");
}

void	controls(t_game *game)
{
	double	move_x;
	double	move_y;

	move_x = game->player.x;
	move_y = game->player.y;
	// printf("move_x = %lf move_y = %lf\n", move_x, move_y);
	if (game->player.rot == 1) //rotate left
		rotate_player(game, 1);
	if (game->player.rot == -1) //rotate right
		rotate_player(game, -1);
	if (game->player.u_d == 1) // Move forward
	{
		move_x += game->player.dir_x * PLAYER_SPEED;
		move_y += game->player.dir_y * PLAYER_SPEED;
	}
	if (game->player.u_d == -1) // Move backward
	{
		move_x -= game->player.dir_x * PLAYER_SPEED;
		move_y -= game->player.dir_y * PLAYER_SPEED;
	}
	if (game->player.l_r == 1) // move right
	{
		move_x -= game->player.dir_y * PLAYER_SPEED;
		move_y += game->player.dir_x * PLAYER_SPEED;
	}
	if (game->player.l_r == -1) // move left
	{
		move_x += game->player.dir_y * PLAYER_SPEED;
		move_y -= game->player.dir_x * PLAYER_SPEED;
	}
	// printf("move_x = %lf move_y = %lf\n", move_x, move_y);
	move_player(game, move_x, move_y);	
}
