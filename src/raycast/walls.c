/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:12:34 by mokutucu          #+#    #+#             */
/*   Updated: 2024/12/19 17:30:06 by chris            ###   ########.fr       */
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

// int	*get_texture(t_game *game, int flag)
// {
// 	if (flag == 0)
// 	{
// 		if (game->ray.ray_angle > M_PI / 2 && game->ray.ray_angle < 3 * (M_PI / 2))
// 			return (game->img.w_texture_add); // west wall
// 		else
// 			return (game->img.e_texture_add); // east wall
// 	}
// 	else
// 	{
// 		if (game->ray.ray_angle > 0 && game->ray.ray_angle < M_PI)
// 			return (game->img.s_texture_add);	// south wall
// 		else
// 			return (game->img.n_texture_add);	// north wall
// 	}
// }

void draw_wall(t_game *game, int ray, int top_pix, int bottom_pix) // draw the wall
{
	int	y;
	unsigned int	color;
	// int	*texture;
	
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
}

void draw_ground(t_game *game, int ray, int bottom_pix)
{
	int y = bottom_pix;

	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(game, ray, y, GROUND_COLOR);
		y++;
	}
}

void draw_sky(t_game *game, int ray, int top_pix)
{
	int y = 0;

	while (y < top_pix)
	{
		my_mlx_pixel_put(game, ray, y, SKY_COLOR);
		y++;
	}
}

void render_wall(t_game *game, int ray)
{
	double wall_h;
	double top_pix;
	double bottom_pix;

	top_pix = 0;
	bottom_pix = 0;
	game->ray.wall_dist *= cos(nor_angle(game->ray.ray_angle - game->player.player_angle)); // fix the fisheye
	wall_h = (TILE_SIZE / game->ray.wall_dist) * ((WIN_WIDTH / 2) / tan(game->view.fov / 2)); // get the wall height
	bottom_pix = (WIN_HEIGHT / 2) + (wall_h / 2); // get the bottom pixel
	top_pix = (WIN_HEIGHT / 2) - (wall_h / 2); // get the top pixel
	if (bottom_pix > WIN_HEIGHT)
		bottom_pix = WIN_HEIGHT;
	if (top_pix < 0)
		top_pix = 0;
	draw_sky(game, ray, top_pix);
	draw_ground(game, ray, bottom_pix);
	draw_wall(game, ray, top_pix, bottom_pix);
}

// rgb(234,182,118) //beige
// rgb(238,238,228) //grey
// rgb(25,118,162) //blue
// rgb(128,57,30) // brown