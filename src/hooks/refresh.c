/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:04:28 by mokutucu          #+#    #+#             */
/*   Updated: 2024/12/19 13:28:31 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	refresh_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;

	mlx_put_image_to_window(game->img.mlx, game->img.mlx_win,
		game->img.img, game->player.x, game->player.y);
	return (0);
}