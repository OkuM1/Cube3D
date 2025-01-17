/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:24:49 by mokutucu          #+#    #+#             */
/*   Updated: 2025/01/17 14:24:52 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	load_textures(t_game *game)
{
	int	i;

	i = 0;
	game->img.textures[0] = mlx_xpm_file_to_image(game->img.mlx,
			game->map.w_text, &game->img.tex_width, &game->img.tex_height);
	game->img.textures[1] = mlx_xpm_file_to_image(game->img.mlx,
			game->map.e_text, &game->img.tex_width, &game->img.tex_height);
	game->img.textures[2] = mlx_xpm_file_to_image(game->img.mlx,
			game->map.s_text, &game->img.tex_width, &game->img.tex_height);
	game->img.textures[3] = mlx_xpm_file_to_image(game->img.mlx,
			game->map.n_text, &game->img.tex_width, &game->img.tex_height);
	while (i < 4)
	{
		if (!game->img.textures[i])
		{
			printf("Failed to load texture %d\n", i);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	draw_logic(t_game *game, double *tex_pos, double *tex_step)
{
	game->tex.y = (int)*tex_pos;
	if (game->tex.y < 0)
		game->tex.y = 0;
	else if (game->tex.y >= game->img.tex_height)
		game->tex.y = game->img.tex_height - 1;
	*tex_pos += *tex_step;
	game->tex.pixel = game->tex.addr + (game->tex.y
			* game->tex.line_length + game->tex.x * (game->tex.bpp / 8));
	game->tex.color = *(int *)game->tex.pixel;
}

void	draw_wall(t_game *game, int ray, int top_pix, int bottom_pix)
{
	int		y;
	double	tex_pos;
	double	tex_step;

	y = top_pix;
	tex_pos = 0;
	texture_wall_hit(game);
	game->tex.texture = get_texture(game);
	game->tex.addr = mlx_get_data_addr(game->tex.texture, &game->tex.bpp,
			&game->tex.line_length, &game->tex.endian);
	game->tex.x = (int)(game->ray.wall_hit_x * game->img.tex_width);
	if (game->ray.wall_side == 'w' || game->ray.wall_side == 's')
		game->tex.x = game->img.tex_width - game->tex.x - 1;
	tex_step = (double)game->img.tex_height / game->ray.wall_heigt;
	if (top_pix < 0)
	{
		tex_pos = -top_pix * tex_step;
		y = 0;
	}
	while (y < bottom_pix && y < WIN_HEIGHT)
	{
		draw_logic(game, &tex_pos, &tex_step);
		my_mlx_pixel_put(game, ray, y, game->tex.color);
		y++;
	}
}

void	check_wall_dir(t_game *game, double h_inter, double v_inter)
{
	if (h_inter < v_inter)
	{
		if (game->ray.angle > 0 && game->ray.angle < M_PI)
			game->ray.wall_side = 's';
		else
			game->ray.wall_side = 'n';
		game->ray.hit_side = 1;
	}
	else if (v_inter < h_inter)
	{
		if (game->ray.angle > M_PI / 2 && game->ray.angle < 3 * M_PI / 2)
			game->ray.wall_side = 'w';
		else
			game->ray.wall_side = 'e';
		game->ray.hit_side = 0;
	}
}

void	render_wall(t_game *game, int ray)
{
	double	top_pix;
	double	bottom_pix;

	top_pix = 0;
	bottom_pix = 0;
	game->ray.wall_dist *= cos(game->ray.angle - game->player.angle);
	if (game->ray.wall_dist < 0.1)
		game->ray.wall_dist = 0.1;
	game->ray.wall_heigt = (TILE_SIZE / game->ray.wall_dist)
		* (WIN_WIDTH / 2) / tan(game->view.fov / 2);
	top_pix = (WIN_HEIGHT / 2) - (game->ray.wall_heigt / 2);
	bottom_pix = (WIN_HEIGHT / 2) + (game->ray.wall_heigt / 2);
	check_wall_dir(game, game->ray.h_inter, game->ray.v_inter);
	draw_wall(game, ray, top_pix, bottom_pix);
	draw_sky(game, ray, top_pix);
	draw_ground(game, ray, bottom_pix);
}
