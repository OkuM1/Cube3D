/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:04:03 by mokutucu          #+#    #+#             */
/*   Updated: 2025/01/17 14:00:27 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_map_level(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.level)
	{
		while (game->map.level[i])
			free(game->map.level[i++]);
		free(game->map.level);
	}
}

void	free_map_files(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.file)
	{
		while (game->map.file[i])
			free(game->map.file[i++]);
		free(game->map.file);
	}
}

void	free_textures(t_game *game)
{
	free(game->map.n_text);
	game->map.n_text = NULL;
	free(game->map.s_text);
	game->map.s_text = NULL;
	free(game->map.w_text);
	game->map.w_text = NULL;
	free(game->map.e_text);
	game->map.e_text = NULL;
}

int	game_exit(t_game *game)
{
	mlx_destroy_image(game->img.mlx, game->img.img);
	mlx_clear_window(game->img.mlx, game->img.mlx_win);
	mlx_destroy_window(game->img.mlx, game->img.mlx_win);
	mlx_destroy_display(game->img.mlx);
	free(game->img.mlx);
	free_textures(game);
	free_map_files(game);
	free_map_level(game);
	exit(0);
}
