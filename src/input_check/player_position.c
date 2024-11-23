/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:07:33 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/23 16:18:39 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void    set_player_angle(t_game *game, char cardinal_direction)
{
    if (cardinal_direction == 'N')
        game->player.rotation_angle = M_PI / 2;  // Facing North (90 degrees)
    else if (cardinal_direction == 'S')
        game->player.rotation_angle = 3 * M_PI / 2;  // Facing South (270 degrees)
    else if (cardinal_direction == 'W')
        game->player.rotation_angle = M_PI;  // Facing West (180 degrees)
    else if (cardinal_direction == 'E')
        game->player.rotation_angle = 0;
}
int find_player_start(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (game->map.level[i] != NULL)
    {
        j = 0;
        while (game->map.level[i][j] != '\0')
        {
            if (game->map.level[i][j] == 'N' || game->map.level[i][j] == 'S' ||
                game->map.level[i][j] == 'W' || game->map.level[i][j] == 'E')
            {
                game->player.x = j * TILE_SIZE + TILE_SIZE / 2;
                game->player.y = i * TILE_SIZE + TILE_SIZE / 2;
                set_player_angle(game, game->map.level[i][j]);
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}