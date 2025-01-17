/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:49:21 by cwick             #+#    #+#             */
/*   Updated: 2025/01/17 13:59:12 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	print_ray(t_game *game)
{
	t_ray	*ray;

	ray = &game->ray;
	printf("\n--- RAY ---\n");
	printf("ray_angle: %f\n", ray->angle);
	printf("wall_dist: %f\n", ray->wall_dist);
	printf("dir_x: %f\n", ray->dir_x);
	printf("dir_y: %f\n", ray->dir_y);
	printf("hor_x: %f\n", ray->hor_x);
	printf("hor_y: %f\n", ray->hor_y);
	printf("vert_x: %f\n", ray->vert_x);
	printf("vert_y: %f\n", ray->vert_y);
	printf("wall_side: %d\n", ray->wall_side);
}

void	print_view(t_game *game)
{
	t_view	*view;

	view = &game->view;
	printf("\n--- VIEW ---\n");
	printf("fov: %f\n", view->fov);
	printf("x: %f\n", view->x);
	printf("y: %f\n", view->y);
	printf("height: %d\n", view->height);
	printf("width: %d\n", view->width);
	printf("zoom: %f\n", view->zoom);
}

void	print_map(t_game *game)
{
	int		i;
	t_map	*map;

	i = 0;
	map = &game->map;
	printf("\n--- MAP ---\n");
	printf("map_size: %d\n", map->map_size);
	printf("n_text: %s\n", map->n_text);
	printf("s_text: %s\n", map->s_text);
	printf("w_text: %s\n", map->w_text);
	printf("e_text: %s\n", map->e_text);
	printf("floor_color: %d\n", map->floor_color);
	printf("ceiling_color: %d\n", map->ceiling_color);
	printf("level_height: %d\n", map->level_height);
	printf("level_width: %d\n", map->level_width);
	while (i < map->level_height)
	{
		printf("level[%d]: %s\n", i, map->level[i]);
		i++;
	}
}

void	print_player(t_game *game)
{
	t_player	*player;

	player = &game->player;
	printf("\n--- PLAYER ---\n");
	printf("player_id: %d\n", player->player_id);
	printf("player_angle: %lf\n", player->angle);
	printf("x: %lf\n", player->x);
	printf("y: %lf\n", player->y);
	printf("dir x: %lf\n", player->dir_x);
	printf("dir y: %lf\n", player->dir_y);
	printf("x in mapgrid: %d\n", player->x_grid);
	printf("y in mapgrid: %d\n", player->y_grid);
	printf("l_r: %d\n", player->l_r);
	printf("u_d: %d\n", player->u_d);
	printf("rot: %d\n", player->rot);
}

void	debugger(t_game *game, char *struct_name)
{
	if (ft_strcmp("img", struct_name) == 0)
		print_img(game);
	else if (ft_strcmp("ray", struct_name) == 0)
		print_ray(game);
	else if (ft_strcmp("view", struct_name) == 0)
		print_view(game);
	else if (ft_strcmp("map", struct_name) == 0)
		print_map(game);
	else if (ft_strcmp("player", struct_name) == 0)
		print_player(game);
}
