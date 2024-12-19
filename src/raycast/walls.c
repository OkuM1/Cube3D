/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:12:34 by mokutucu          #+#    #+#             */
/*   Updated: 2024/12/19 11:46:05 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void my_mlx_pixel_put(t_game *game, int x, int y, unsigned int color) // put the pixel
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = game->img.img_address + (y * game->img.line_length) + (x * (game->img.bpp / 8));
	if (dst)
		*(unsigned int *)dst = color;
}

float nor_angle(float angle) // normalize the angle
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

int rgba_to_int(int r, int g, int b, int a) {
    return (a << 24) | (r << 16) | (g << 8) | b;
}

void draw_floor_ceiling(t_game *game, int ray, int t_pix, int b_pix)
{
	int	i;
	int	floor_color;
	int	ceiling_color;

	i = b_pix;
	floor_color = rgba_to_int(95,203,249,255);
	ceiling_color = rgba_to_int(69,123,5,255);
	while (i > WIN_HEIGHT / 2)
	{
		my_mlx_pixel_put(game->img.mlx, ray, i, floor_color); //floor
		i++;
	}
	i = t_pix;
	while (i < b_pix / 2)
	{
		my_mlx_pixel_put(game->img.mlx, ray, i, ceiling_color); // ceiling
		i++;
	}
}

int get_color(t_game *game, int flag) // get the color of the wall
{
	game->ray.ray_angle = nor_angle(game->ray.ray_angle); // normalize the angle
	if (flag == 0)
	{
		if (game->ray.ray_angle > M_PI / 2 && game->ray.ray_angle < 3 * (M_PI / 2))
			return (rgba_to_int(234,182,118,255)); // west wall
		else
			return (rgba_to_int(238,238,228,255)); // east wall
	}
	else
	{
		if (game->ray.ray_angle > 0 && game->ray.ray_angle < M_PI)
			return (rgba_to_int(25,118,162,255)); // south wall
		else
			return (rgba_to_int(128,57,30,255)); // north wall
	}
}

// rgb(234,182,118) //beige
// rgb(238,238,228) //grey
// rgb(25,118,162) //blue
// rgb(128,57,30) // brown