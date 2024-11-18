/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:04:28 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/16 20:44:16 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	refresh_game(t_game *game)
{
	mlx_put_image_to_window(game->img.mlx, game->img.mlx_win,
		game->img.img, 0, 0);
	return (0);
}