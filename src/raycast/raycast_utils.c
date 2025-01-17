/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:48:27 by cwick             #+#    #+#             */
/*   Updated: 2025/01/17 13:03:57 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	clear_image(t_game *game)
{
	int		i;
	int		total_pixels;
	char	*pixel_buffer;

	i = 0;
	total_pixels = WIN_WIDTH * WIN_HEIGHT;
	pixel_buffer = game->img.img_address;
	while (i < total_pixels)
	{
		*(unsigned int *)pixel_buffer = 0x000000;
		pixel_buffer += (game->img.bpp / 8);
		i++;
	}
}

// transfers degree to radians
double	deg_to_rad(double a)
{
	return (a * M_PI / 180);
}

// normalize the angle
void	nor_angle(double *angle)
{
	while (*angle < 0)
		*angle += 2 * M_PI;
	while (*angle > 2 * M_PI)
		*angle -= 2 * M_PI;
}

int	check_boundaries(t_game *game, char c)
{
	if (c == 'h')
	{
		if (game->ray.hor_x < 0
			|| game->ray.hor_x >= game->map.level_width * TILE_SIZE
			|| game->ray.hor_y < 0
			|| game->ray.hor_y >= game->map.level_height * TILE_SIZE)
			return (1);
	}
	if (c == 'v')
	{
		if (game->ray.vert_x < 0
			|| game->ray.vert_x >= game->map.level_width * TILE_SIZE
			|| game->ray.vert_y < 0
			|| game->ray.vert_y >= game->map.level_height * TILE_SIZE)
			return (1);
	}
	return (0);
}

int	control_wall_hit(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0 || map_x >= game->map.level_width
		|| map_y >= game->map.level_height
		|| game->map.level[map_y][map_x] == '1')
		return (1);
	return (0);
}
