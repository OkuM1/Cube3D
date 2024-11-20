/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:16:09 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/20 18:08:40 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    render(t_game *game)
{
    game->img.mlx = mlx_init();
    game->img.mlx_win = mlx_new_window(game->img.mlx, 800, 600, "cub3d");
    game->img.img = mlx_new_image(game->img.mlx, 800, 600);
    game->img.img_address = mlx_get_data_addr(game->img.img, &game->img.bpp,
			    &game->img.line_length,  &game->img.endian);
    mlx_put_image_to_window(game->img.mlx, game->img.mlx_win, game->img.img, 0, 0);
    mlx_key_hook(game->img.mlx_win, key_hook, game);
    mlx_hook(game->img.mlx_win, 17, 1L << 0, game_exit, game);
	mlx_expose_hook(game->img.mlx_win, refresh_game, game);
    mlx_loop(game->img.mlx);
}

void init_all(t_game *game)
{
	game->map.map = NULL;
	game->map.n_text = NULL;
	game->map.s_text = NULL;
	game->map.w_text = NULL;
	game->map.e_text = NULL;
	game->map.floor_color[0] = -1;
	game->map.floor_color[1] = -1;
	game->map.floor_color[2] = -1;
	game->map.ceiling_color[0] = -1;
	game->map.ceiling_color[1] = -1;
	game->map.ceiling_color[2] = -1;
	game->map.map_size = 0;
	game->map.level = NULL;
	game->player.player_id = 0;
	
}

int main(int ac, char **av)
{
	t_game	game;
	
	init_all(&game);
	if (check_input(ac, av, &game) != 0)
		return (0);
	
	int i = 0;
    while (game.map.level[i])
    {
        printf("%s", game.map.level[i]);
        i++;
    }
	printf("\n");

	
	render(&game);
	return 0;
}