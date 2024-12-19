/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:02:18 by chris             #+#    #+#             */
/*   Updated: 2024/12/19 11:54:07 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	unit_circle(float angle, char c) // Check if the angle intersects with the unit circle
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

int	intersection_check(float angle, float *intersection, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*intersection += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*intersection += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	wall_hit(float x, float y, t_game *game)
{
	int		x_map;
	int		y_map;

	if (x < 0 || y < 0)
		return (0);
	x_map = floor(x / TILE_SIZE); // Get the x position on the map
	y_map = floor(y / TILE_SIZE); // Get the y position on the map
	if (y_map >= game->map.level_height || x_map >= game->map.level_width)
		return (0);
	if (game->map.level[y_map] != NULL && x_map < (int)strlen(game->map.level[y_map]))
	{
		if (game->map.level[y_map][x_map] == '1')
			return (0);
	}
	return (1);
}

float	get_h_intersection(t_game *game, float angle)
{
	float	hor_x;
	float	hor_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angle);
	hor_y = floor(game->player.y / TILE_SIZE) * TILE_SIZE;
	if (angle > 0 && angle < M_PI)
    	hor_y += TILE_SIZE;
	hor_x = game->player.x + (hor_y - game->player.y) / tan(angle);
	pixel = intersection_check(angle, &hor_y, &y_step, 1);
	if ((unit_circle(angle, 'y') && x_step > 0) || (!unit_circle(angle, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(hor_x, hor_y - pixel, game))
	{
		hor_x += x_step;
		hor_y += y_step;
	}
	printf("Horizontal: X: %f, Y: %f, X_Step: %f, Y_Step: %f\n", hor_x, hor_y, x_step, y_step);
	return (sqrt(pow(hor_x - game->player.x, 2) + pow(hor_y - game->player.y, 2)));
}

double capped_tan(double angle) {
    double tan_value = tan(angle);
    if (fabs(tan_value) > 1e6)
        tan_value = tan_value > 0 ? 1e6 : -1e6;
    return tan_value;
}

float	get_v_intersection(t_game *game, float angle)
{
	float	ver_x;
	float	ver_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * capped_tan(angle);
	ver_x = floor(game->player.x / TILE_SIZE) * TILE_SIZE;
	ver_y = 0;
	pixel = intersection_check(angle, &ver_x, &x_step, 0);
	if (angle == M_PI / 2 || angle == 3 * M_PI / 2)
    	ver_y = game->player.y;  // Set Y to player Y for vertical angles
	else
        ver_y = game->player.y + (ver_x - game->player.x) * tan(angle);  // Calculate vertical intersection
	if ((unit_circle(angle, 'x') && y_step < 0) || (!unit_circle(angle, 'x') && y_step > 0))
		y_step *= -1;
	printf("Initial Vertical Intersection: Ver_X: %f, Ver_Y: %f, Angle: %f\n", ver_x, ver_y, angle);
	while (wall_hit(ver_x - pixel, ver_y, game))
	{
		ver_x += x_step;
		ver_y += y_step;
	}
	printf("Vertical: X: %f, Y: %f, X_Step: %f, Y_Step: %f\n", ver_x, ver_y, x_step, y_step);
	return (sqrt(pow(ver_x - game->player.x, 2) + pow(ver_y - game->player.y, 2)));
}

void	cast_rays(t_game *game)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	game->ray.ray_angle = nor_angle(game->ray.ray_angle);
	game->ray.ray_angle = game->player.player_angle - (game->view.fov / 2); // Initial ray angle
	while (ray < WIN_WIDTH)
	{
		game->ray.wall_flag = 0;
		h_inter = get_h_intersection(game, nor_angle(game->ray.ray_angle)); // Get horizontal intersection
		v_inter = get_v_intersection(game, nor_angle(game->ray.ray_angle)); // Get vertical intersection

		if (v_inter <= h_inter)
			game->ray.wall_dist = v_inter;
		else
		{
			game->ray.wall_dist = h_inter;
			game->ray.wall_flag = 1; // Flag for horizontal wall hit
		}
		render_wall(game, ray); // Render the wall
		ray++; // Move to the next ray
		game->ray.ray_angle += nor_angle(game->view.fov / WIN_WIDTH); // Increment the angle
	}
}
