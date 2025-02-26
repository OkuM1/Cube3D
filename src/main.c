/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:16:09 by mokutucu          #+#    #+#             */
/*   Updated: 2025/01/17 13:24:56 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	game_loop(t_game *game)
{
	create_image(game);
	controls(game);
	mlx_put_image_to_window(game->img.mlx,
		game->img.mlx_win, game->img.img, 0, 0);
	return (0);
}

void	render_game(t_game *game)
{
	game->img.mlx = mlx_init();
	game->img.mlx_win = mlx_new_window(game->img.mlx,
			WIN_WIDTH, WIN_HEIGHT, "cub3d");
	game->img.img = mlx_new_image(game->img.mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.img_address = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_length, &game->img.endian);
	load_textures(game);
	mlx_hook(game->img.mlx_win, 17, 1L << 0, game_exit, game);
	mlx_hook(game->img.mlx_win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->img.mlx_win, 3, 1L << 1, handle_keyrelease, game);
	mlx_expose_hook(game->img.mlx_win, refresh_game, game);
	mlx_loop_hook(game->img.mlx, &game_loop, game);
	mlx_loop(game->img.mlx);
}

int	main(int ac, char **av)
{
	t_game	game;

	init_all(&game);
	if (check_input(ac, av, &game) != 0)
		return (0);
	render_game(&game);
	return (0);
}
