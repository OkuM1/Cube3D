/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:12:34 by mokutucu          #+#    #+#             */
/*   Updated: 2024/12/10 17:45:04 by cwick            ###   ########.fr       */
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

void draw_wall(t_game *game, int ray, int top_pix, int bottom_pix) // draw the wall
{
	int	y;
	unsigned int	color;
	// int	texture;
	y = top_pix;
	color = 0;
	// texture = get_texture(game, game->ray.wall_flag);
	color = get_color(game, game->ray.wall_flag);
	if (y < bottom_pix)
	{
		while (y < bottom_pix)
		{
			my_mlx_pixel_put(game, ray, y, color);
			y++;
		}
	}
	printf("Ray: %d, Top: %d, Bottom: %d, Color: %u\n", ray, top_pix, bottom_pix, color);
}

void render_wall(t_game *game, int ray) // render the wall
{
	double wall_h;
	double bottom_pix;
	double top_pix;

	game->ray.wall_dist *= cos(nor_angle(game->ray.ray_angle - game->player.player_angle)); // fix the fisheye
	wall_h = (TILE_SIZE / game->ray.wall_dist) * ((WIN_WIDTH / 2) / tan(game->view.fov / 2)); // get the wall height
	printf("wall_h: %lf\n", wall_h);
	bottom_pix = (WIN_HEIGHT / 2) + (wall_h / 2); // get the bottom pixel
	top_pix = (WIN_HEIGHT / 2) - (wall_h / 2); // get the top pixel
	printf("Ray: %d, Top: %f, Bottom: %f, Wall_H: %f\n", ray, top_pix, bottom_pix, wall_h);
	if (bottom_pix > WIN_HEIGHT)
		bottom_pix = WIN_HEIGHT;
	if (top_pix < 0)
		top_pix = 0;
	draw_wall(game, ray, top_pix, bottom_pix);
	// draw_floor_ceiling(game, ray, top_pix, bottom_pix); // draw the floor and the ceiling
}

// rgb(234,182,118) //beige
// rgb(238,238,228) //grey
// rgb(25,118,162) //blue
// rgb(128,57,30) // brown