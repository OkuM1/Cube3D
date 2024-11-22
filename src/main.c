/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:16:09 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/22 16:43:28 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_image(t_game *game, int i, int j)
{
	if (game->map.level[i][j] == '1')
		mlx_put_image_to_window(game->img.mlx, game->img.mlx_win,
			game->map.n_text, j * 64, i * 64);
}
void	loading_graphics(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.level_height)
	{
		j = 0;
		while (game->map.level[i][j])
		{
			put_image(game, i, j);
			j++;
		}
		i++;
	}
}

void    render_game(t_game *game)
{    
    int width;
    int height;

    
    game->img.mlx = mlx_init();
    game->img.mlx_win = mlx_new_window(game->img.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
    //game->img.img = mlx_new_image(game->img.mlx, WIN_WIDTH, WIN_HEIGHT);

    printf("%s", game->map.n_text);
    printf("Path length: %zu\n", strlen(game->map.n_text));
    
    // print return value of mlx_xpm_file_to_image(game->img.mlx, game->map.n_text, &width, &height)
    printf("Return value: %p\n", mlx_xpm_file_to_image(game->img.mlx, game->map.n_text, &width, &height));
	// TODO: LOAD ALL INTO IMG BUFFER HERE			
	game->map.n_text = mlx_xpm_file_to_image(game->img.mlx, game->map.n_text, &width, &height);

    game->img.img_address = mlx_get_data_addr(game->img.img, &game->img.bpp,
			    &game->img.line_length,  &game->img.endian);
    
    //mlx_put_image_to_window(game->img.mlx, game->img.mlx_win, game->img.img, 0, 0);
    loading_graphics(game);
    mlx_key_hook(game->img.mlx_win, key_hook, game);
    mlx_hook(game->img.mlx_win, 17, 1L << 0, game_exit, game);
	mlx_expose_hook(game->img.mlx_win, refresh_game, game);
    mlx_loop(game->img.mlx);
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
	printf("-----GAME STARTED-----\n");

	render_game(&game);
	
	return 0;
}