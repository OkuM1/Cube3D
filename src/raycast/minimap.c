/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:01:54 by chris             #+#    #+#             */
/*   Updated: 2025/01/09 14:23:25 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Bresenham's line algorithm
void	draw_line(t_game *game, int end_x, int end_y, int color)
{
	int err;
	int err2;
	int	current_x;
	int current_y;

	current_x = (int)game->player.x;
	current_y = (int)game->player.y;
	game->ray.delta_x = abs(end_x - current_x);
	game->ray.delta_y = abs(end_y - current_y);
	if (current_x < end_x) // Step direction for x
		game->ray.step_x = 1;
	else
		game->ray.step_x = -1;
	if (current_y < end_y) // Step direction for y
		game->ray.step_y = 1;
	else
		game->ray.step_y = -1;
	err = game->ray.delta_x - game->ray.delta_y;
	while (1)
	{
		my_mlx_pixel_put(game, current_x, current_y, color);
		if (current_x == end_x && current_y == end_y)
			break;
		err2 = 2 * err;
		if (err2 > -game->ray.delta_y)
		{
			err -= game->ray.delta_y;
			current_x += game->ray.step_x;
		}
		if (err2 < game->ray.delta_x)
		{
			err += game->ray.delta_x;
			current_y += game->ray.step_y;
		}
	}
}

void	draw_player_direction(t_game *game)
{
	double	current_angle;
	double	end_angle;
	double	end_x;
	double	end_y;
	double	h_inter;
	double	v_inter;

	end_y = 0;
	end_x = 0;
	h_inter = 0;
	v_inter = 0;
	game->ray.angle = game->player.angle - (game->view.fov / 2);
	current_angle = game->ray.angle;
	end_angle = game->player.angle + (game->view.fov / 2);
	while (current_angle <= end_angle)
	{
		game->ray.dir_x = cos(current_angle);
		game->ray.dir_y = sin(current_angle);
		h_inter = get_h_inter(game);
		v_inter = get_v_inter(game);
		// printf("h_inter: %lf v_inter: %lf\n", h_inter, v_inter);
		if (h_inter < v_inter)
		{	
			end_x = game->ray.hor_x;
			end_y = game->ray.hor_y;
		}
		else if (v_inter < h_inter)
		{
			end_x = game->ray.vert_x;
			end_y = game->ray.vert_y;
		}
		// printf("End X: %lf, End Y: %lf\n", end_x, end_y);
		draw_line(game, (int)end_x, (int)end_y, 0x00FF00);
		current_angle += deg_to_rad(1);
	}
}

void	draw_player(t_game *game)
{
	int	pl_size;
	int	x;
	int	y;

	pl_size = 4;
	y = game->player.y - pl_size / 2;
	while (y < game->player.y + pl_size / 2)
	{
		x = game->player.x - pl_size / 2;
		while (x < game->player.x + pl_size / 2)
		{
			my_mlx_pixel_put(game, x, y, PLAYER_COLOR);
			x++;
		}
		y++;
	}
}

void	draw_rectangle(t_game *game, int x_len, int y_len, unsigned int color)
{
	int	rect_x;
	int	rect_y;

	rect_y = y_len;
	while (rect_y < y_len + (TILE_SIZE))
	{
		rect_x = x_len;
		while (rect_x < x_len + (TILE_SIZE))
		{
			my_mlx_pixel_put(game, rect_x, rect_y, color);
			rect_x++;
		}
		rect_y++;
	}
}

void	draw_map2d(t_game *game)
{
	int				y;
	int				x;
	int				x_len;
	int				y_len;
	unsigned int	color;

	y = 0;
	while (y < game->map.level_height)
	{
		x = 0;
		while (x < game->map.level_width)
		{	
			if (game->map.level[y][x] == '1')
				color = 0xFFFFFF;
			else
				color = 0x757575;
			x_len = x * (TILE_SIZE);
			y_len = y * (TILE_SIZE);
			draw_rectangle(game, x_len, y_len, color);
			x++;
		}
		y++;
	}
}

void	create_minimap(t_game *game)
{
	draw_map2d(game);
	draw_player(game);
	draw_player_direction(game);
}