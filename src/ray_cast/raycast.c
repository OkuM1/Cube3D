/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:02:18 by chris             #+#    #+#             */
/*   Updated: 2024/12/09 13:07:13 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

float get_x_hit(t_game game, float angle)
{
	float	hor_x;
	float	hor_y;
	float	dist_x;
	float	dist_y;
	int		pixel;

	dist_y = TILE_SIZE;
	
}

float	normalize_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

void cast_rays (t_game *game)
{
	double x_hit;
	double y_hit;
	int		ray_counter;

	ray_counter = 0;
	game->ray.ray_angle = game->player.player_angle - (game->view.fov / 2);
	while (ray_counter < WIN_WIDTH)
	{
		game->ray.wall_flag = 0;
		x_hit = get_x_hit(game, normalize_angle(game->ray.ray_angle));
		y_hit = get_y_hit(game, normalize_angle(game->ray.ray_angle));

	}

	
}
