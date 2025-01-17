/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:59:28 by mokutucu          #+#    #+#             */
/*   Updated: 2025/01/17 13:42:13 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	handle_keyrelease(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == ESC)
		game_exit(game);
	else if (keycode == A)
		game->player.l_r = 0;
	else if (keycode == D)
		game->player.l_r = 0;
	else if (keycode == S)
		game->player.u_d = 0;
	else if (keycode == W)
		game->player.u_d = 0;
	else if (keycode == L_ARROW)
		game->player.rot = 0;
	else if (keycode == R_ARROW)
		game->player.rot = 0;
	return (0);
}

int	handle_keypress(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == ESC)
		game_exit(game);
	else if (keycode == A)
		game->player.l_r = -1;
	else if (keycode == D)
		game->player.l_r = 1;
	else if (keycode == S)
		game->player.u_d = -1;
	else if (keycode == W)
		game->player.u_d = 1;
	else if (keycode == L_ARROW)
		game->player.rot = -1;
	else if (keycode == R_ARROW)
		game->player.rot = 1;
	return (0);
}
