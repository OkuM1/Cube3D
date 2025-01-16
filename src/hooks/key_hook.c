/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:59:28 by mokutucu          #+#    #+#             */
/*   Updated: 2024/12/21 14:26:00 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	handle_keyrelease(int keycode, void *param)
{
	t_game *game = (t_game *)param;

	if (keycode == ESC) // Exit the game
		game_exit(game);
	else if (keycode == A) // Stop move left
		game->player.l_r = 0;
	else if (keycode == D) // Stop move right
		game->player.l_r = 0;
	else if (keycode == S) // Stop move down
		game->player.u_d = 0;
	else if (keycode == W) // Stop move up
		game->player.u_d = 0;
	else if (keycode == L_ARROW) // Stop rotate left
		game->player.rot = 0;
	else if (keycode == R_ARROW) // Stop rotate right
		game->player.rot = 0;
	return (0);
}

int	handle_keypress(int keycode, void *param)
{
	t_game *game = (t_game *)param;

	if (keycode == ESC) // Exit the game
		game_exit(game);
	else if (keycode == A) // Move left
		game->player.l_r = -1;
	else if (keycode == D) // Move right
		game->player.l_r = 1;
	else if (keycode == S) // Move down
		game->player.u_d = -1;
	else if (keycode == W) // Move up
		game->player.u_d = 1;
	else if (keycode == L_ARROW) // Rotate left
		game->player.rot = -1;
	else if (keycode == R_ARROW) // Rotate right
		game->player.rot = 1;
	return (0);
}
