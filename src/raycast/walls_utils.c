/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:14:25 by cwick             #+#    #+#             */
/*   Updated: 2025/01/17 12:21:53 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, unsigned int color)
{
	char	*pixel_buffer;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	pixel_buffer = game->img.img_address + (y * game->img.line_length)
		+ (x * game->img.bpp / 8);
	if (pixel_buffer)
		*(unsigned int *)pixel_buffer = color;
}

void	draw_ground(t_game *game, int ray, int bottom_pix)
{
	int	y;

	y = bottom_pix;
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(game, ray, y, game->map.floor_color);
		y++;
	}
}

void	draw_sky(t_game *game, int ray, int top_pix)
{
	int	y;

	y = 0;
	while (y < top_pix)
	{
		my_mlx_pixel_put(game, ray, y, game->map.ceiling_color);
		y++;
	}
}

void	*get_texture(t_game *game)
{
	if (game->ray.wall_side == 'w')
		return (game->img.textures[0]);
	else if (game->ray.wall_side == 'e')
		return (game->img.textures[1]);
	else if (game->ray.wall_side == 's')
		return (game->img.textures[2]);
	else if (game->ray.wall_side == 'n')
		return (game->img.textures[3]);
	return (NULL);
}

void	texture_wall_hit(t_game *game)
{
	if (game->ray.hit_side == 1)
		game->ray.wall_hit_x = fmod(game->ray.hor_x, TILE_SIZE) / TILE_SIZE;
	else
		game->ray.wall_hit_x = fmod(game->ray.vert_y, TILE_SIZE) / TILE_SIZE;
	game->ray.wall_hit_x -= floor(game->ray.wall_hit_x);
}
