/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:55:42 by cwick             #+#    #+#             */
/*   Updated: 2025/01/17 13:57:40 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	print_img(t_game *game)
{
	t_img	*img;

	img = &game->img;
	printf("\n--- IMG ---\n");
	printf("mlx: %p\n", img->mlx);
	printf("mlx_win: %p\n", img->mlx_win);
	printf("img: %p\n", img->img);
	printf("img_address: %s\n", img->img_address);
	printf("bpp: %d\n", img->bpp);
	printf("line_length: %d\n", img->line_length);
	printf("endian: %d\n", img->endian);
	printf("width: %d\n", img->width);
	printf("height: %d\n", img->height);
	printf("n_texture_add: %s\n", img->n_texture_add);
	printf("s_texture_add: %s\n", img->s_texture_add);
	printf("w_texture_add: %s\n", img->w_texture_add);
	printf("e_texture_add: %s\n", img->e_texture_add);
}
