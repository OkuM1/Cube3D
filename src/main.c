/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:16:09 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/18 18:46:49 by chris            ###   ########.fr       */
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

int main(int ac, char **av)
{
	t_game	game;
	t_map	map;

	// init_structs(game, map);
	if (check_input(ac, av, &game, &map) != 0)
		return (0);
	if (parse_file(av, &game) != 0)
		return (0);
	printf("%s\n", game.map.s_text);
	printf("Floor :%d\n", game.map.floor_color[0]);
	printf("Ceiling %d\n", game.map.ceiling_color[1]);
		
	render(&game);
	return 0;
}