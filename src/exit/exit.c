/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:04:03 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/22 16:59:27 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int game_exit(t_game *game)
{
    mlx_destroy_image(game->img.mlx, game->img.img);
	mlx_clear_window(game->img.mlx, game->img.mlx_win);
	mlx_destroy_window(game->img.mlx, game->img.mlx_win);
	mlx_destroy_display(game->img.mlx);
	free(game->img.mlx);
	exit(0);
}