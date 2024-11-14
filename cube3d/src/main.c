/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:16:09 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/14 18:17:41 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void    render(t_game *game)
{
    game->img.mlx = mlx_init();
    game->img.mlx_win = mlx_new_window(game->img.mlx, 800, 600, "cub3d");
    game->img.img = mlx_new_image(game->img.mlx, 800, 600);
    game->img.img_address = mlx_get_data_addr(game->img.img, &game->img.bpp,
			    &game->img.line_length,  &game->img.endian);
    mlx_put_image_to_window(game->img.mlx, game->img.mlx_win, game->img.img, 0, 0);
    mlx_loop(game->img.mlx);
}
int main(int ac, char **av)
{
    if (ac != 2)
    {
        printf("Wrong arg count!\n");
        return (0);
    }
    (void) av;
    
    t_game game;

    render(&game);
    return 0;
}