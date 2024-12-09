/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:12:34 by mokutucu          #+#    #+#             */
/*   Updated: 2024/12/09 16:42:33 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void my_mlx_pixel_put(t_game *game, int x, int y, int color) // put the pixel
{
	if (x < 0) // check the x position
		return ;
	else if (x >= WIN_WIDTH)
		return ;
	if (y < 0) // check the y position
		return ;
	else if (y >= WIN_HEIGHT)
		return ;
	mlx_pixel_put(game->img.img, game->img.mlx_win, x, y, color); // put the pixel
}

float nor_angle(float angle) // normalize the angle
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

void draw_floor_ceiling(t_game *game, int ray, int t_pix, int b_pix) // draw the floor and the ceiling
{
    int  i;
 //int  c;

	i = b_pix;
	while (i < WIN_HEIGHT)
		my_mlx_pixel_put(game->img.mlx, ray, i++, 0x0000FF); // floor
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(game->img.mlx, ray, i++, 0xFFFF00); // ceiling
}

int get_color(t_game *game, int flag) // get the color of the wall
{
	game->ray.ray_angle = nor_angle(game->ray.ray_angle); // normalize the angle
	if (flag == 0)
	{
		if (game->ray.ray_angle > M_PI / 2 && game->ray.ray_angle < 3 * (M_PI / 2))
			return (0xB5B5B5FF); // west wall
		else
			return (0xB5B5B5FF); // east wall
	}
	else
	{
		if (game->ray.ray_angle > 0 && game->ray.ray_angle < M_PI)
			return (0xF5F5F5FF); // south wall
		else
			return (0xF5F5F5FF); // north wall
	}
}

void draw_wall(t_game *game, int ray, int t_pix, int b_pix) // draw the wall
{
	int color;

	color = get_color(game, game->ray.wall_flag);
	while (t_pix < b_pix)
		my_mlx_pixel_put(game, ray, t_pix++, color);
}

void render_wall(t_game *game, int ray) // render the wall
{
	double wall_h;
	double b_pix;
	double t_pix;

	game->ray.wall_dist *= cos(nor_angle(game->ray.ray_angle - game->player.player_angle)); // fix the fisheye
	wall_h = (TILE_SIZE / game->ray.wall_dist) * ((WIN_WIDTH / 2) / tan(game->view.fov / 2)); // get the wall height
	b_pix = (WIN_HEIGHT / 2) + (wall_h / 2); // get the bottom pixel
	t_pix = (WIN_HEIGHT / 2) - (wall_h / 2); // get the top pixel
	if (b_pix > WIN_HEIGHT) // check the bottom pixel
		b_pix = WIN_HEIGHT;
	if (t_pix < 0) // check the top pixel
		t_pix = 0;
	draw_wall(game, ray, t_pix, b_pix); // draw the wall
	draw_floor_ceiling(game, ray, t_pix, b_pix); // draw the floor and the ceiling
}