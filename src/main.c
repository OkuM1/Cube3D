/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:16:09 by mokutucu          #+#    #+#             */
/*   Updated: 2024/12/10 16:35:42 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void	put_image(t_game *game, int i, int j)
// {
// 	if (game->map.level[i][j] == '1')
// 		mlx_put_image_to_window(game->img.mlx, game->img.mlx_win,
// 			game->img.n_texture_add, j * 64, i * 64);
// }

// void	loading_graphics(t_game *game)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < game->map.level_height)
// 	{
// 		j = 0;
// 		while (game->map.level[i][j])
// 		{
// 			put_image(game, i, j);
// 			j++;
// 		}
// 		i++;
// 	}
// }

void    init_view(t_game *game)
{
    game->view.x = 0;
    game->view.y = 0;
    game->view.height = WIN_HEIGHT;
    game->view.width = WIN_WIDTH;
    game->view.zoom = 1.0;
}

int	game_loop(t_game *game) // Game loop for rendering and updating the game
{
    // t_game *game;

    // game = (t_game *)data; // Cast the passed data to the game structure
    
    // Clear previous frame image
    mlx_clear_window(game->img.mlx, game->img.mlx_win);
    
    // Cast rays for rendering the 3D scene
    cast_rays(game);
    
    // Draw the new frame to the window
    mlx_put_image_to_window(game->img.mlx, game->img.mlx_win, game->img.img, 0, 0);
	return (0);
}

void	render_game(t_game *game)
{	
	init_view(game);
	game->img.mlx = mlx_init();
	game->img.mlx_win = mlx_new_window(game->img.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	game->img.img = mlx_new_image(game->img.mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.img_address = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.line_length, &game->img.endian);
    mlx_hook(game->img.mlx_win, 17, 1L << 0, game_exit, game);
	mlx_expose_hook(game->img.mlx_win, refresh_game, game);
	mlx_key_hook(game->img.mlx_win, &key_hook, game);
	mlx_loop_hook(game->img.mlx, &game_loop, game);
	mlx_loop(game->img.mlx);
}
    //mlx_put_image_to_window(game->img.mlx, game->img.mlx_win, game->img.img, 0, 0);
    // loading_graphics(game);


int main(int ac, char **av)
{
	t_game	game;
	
	init_all(&game);
	if (check_input(ac, av, &game) != 0)
		return (0);
	printf("\n");
	printf("-----GAME STARTED-----\n");
    printf("Player starting position: x = %f, y = %f\n", game.player.x, game.player.y);
    printf("Player starting angle: %f radians\n", game.player.player_angle);
	render_game(&game);
	return 0;
}