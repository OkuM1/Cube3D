/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:07:33 by mokutucu          #+#    #+#             */
/*   Updated: 2025/01/04 06:04:39 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	set_player_angle(t_game *game, char cardinal_direction)
{
	if (cardinal_direction != 'N' && cardinal_direction != 'E'
		&& cardinal_direction != 'S' && cardinal_direction != 'W')
		return (1);
	if (cardinal_direction == 'N')
		game->player.angle = 3 * M_PI / 2;
	else if (cardinal_direction == 'S')
		game->player.angle = M_PI / 2;
	else if (cardinal_direction == 'W')
		game->player.angle = M_PI;
	else if (cardinal_direction == 'E')
		game->player.angle = 0;
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
	return (0);
}

int find_player_start(t_game *game)
{
	int y;
	int x;

	y = 0;
	while (game->map.level[y] != NULL)
	{
		x = 0;
		while (game->map.level[y][x] != '\0')
		{
			if (game->map.level[y][x] == 'N' || game->map.level[y][x] == 'S' ||
				game->map.level[y][x] == 'W' || game->map.level[y][x] == 'E')
			{
				game->player.x = x * TILE_SIZE + (TILE_SIZE / 2);
				game->player.y = y * TILE_SIZE + (TILE_SIZE / 2);
				game->player.x_grid = x;
				game->player.y_grid = y;
				if (set_player_angle(game, game->map.level[y][x]) == 1)
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
