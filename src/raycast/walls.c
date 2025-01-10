/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:12:34 by mokutucu          #+#    #+#             */
/*   Updated: 2025/01/10 14:56:22 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void my_mlx_pixel_put(t_game *game, int x, int y, unsigned int color) // put the pixel
{
	char	*pixel_buffer;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	pixel_buffer = game->img.img_address + (y * game->img.line_length) + (x * game->img.bpp / 8);
	if (pixel_buffer)
		*(unsigned int *)pixel_buffer = color;
}

int rgba_to_int(int r, int g, int b, int a)
{
	return (a << 24) | (r << 16) | (g << 8) | b;
}

void draw_ground(t_game *game, int ray, int bottom_pix)
{
	int y = bottom_pix;

	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(game, ray, y, GROUND_COLOR);
		y++;
	}
}

void draw_sky(t_game *game, int ray, int top_pix)
{
	int y = 0;

	while (y < top_pix)
	{
		my_mlx_pixel_put(game, ray, y, SKY_COLOR);
		y++;
	}
}

void load_textures(t_game *game)
{
	int i;

	i = 0;
	game->img.textures[0] = mlx_xpm_file_to_image(game->img.mlx, game->map.w_text, &game->img.tex_width, &game->img.tex_height);
	game->img.textures[1] = mlx_xpm_file_to_image(game->img.mlx, game->map.e_text, &game->img.tex_width, &game->img.tex_height);
	game->img.textures[2] = mlx_xpm_file_to_image(game->img.mlx, game->map.s_text, &game->img.tex_width, &game->img.tex_height);
	game->img.textures[3] = mlx_xpm_file_to_image(game->img.mlx, game->map.n_text, &game->img.tex_width, &game->img.tex_height);
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

void	*get_texture(t_game *game)
{	
	if (game->ray.wall_side == 'w')
		return game->img.textures[0];
	else if (game->ray.wall_side == 'e')
		return game->img.textures[1];
	else if (game->ray.wall_side == 's')
		return game->img.textures[2];
	else if (game->ray.wall_side == 'n')
		return game->img.textures[3];
	return (NULL);
}

void	texture_wall_hit(t_game *game)
{
	if (game->ray.hit_side == 1)
		game->ray.wall_hit_x = fmod(game->ray.hor_x, TILE_SIZE) / TILE_SIZE;
	else
		game->ray.wall_hit_x = fmod(game->ray.vert_y, TILE_SIZE) / TILE_SIZE;
	game->ray.wall_hit_x -= floor(game->ray.wall_hit_x);
}


void draw_wall(t_game *game, int ray, int top_pix, int bottom_pix)
{
	int		y;
	double	tex_pos;
	double	tex_step;
	
	y = top_pix;
	tex_pos = 0;
	texture_wall_hit(game);
	game->tex.texture = get_texture(game);
	game->tex.addr = mlx_get_data_addr(game->tex.texture, &game->tex.bpp, &game->tex.line_length, &game->tex.endian);
	game->tex.x = (int)(game->ray.wall_hit_x * game->img.tex_width);
	if (game->ray.wall_side == 'w' || game->ray.wall_side == 's')	//flip texture
		game->tex.x = game->img.tex_width - game->tex.x - 1;
	tex_step = (double)game->img.tex_height / game->ray.wall_heigt;
	if (top_pix < 0)
	{
		tex_pos = -top_pix * tex_step;
		y = 0;
	}	
	while (y < bottom_pix && y < WIN_HEIGHT)
	{
		game->tex.y = (int)tex_pos;
		if (game->tex.y < 0)
			game->tex.y = 0;
		else if (game->tex.y >= game->img.tex_height)
			game->tex.y = game->img.tex_height - 1;
		tex_pos += tex_step;
		game->tex.pixel = game->tex.addr + (game->tex.y * game->tex.line_length + game->tex.x * (game->tex.bpp / 8));
		game->tex.color = *(int *)game->tex.pixel;
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

void render_wall(t_game *game, int ray)
{
	double top_pix;
	double bottom_pix;

	top_pix = 0;
	bottom_pix = 0;
	game->ray.wall_dist *= cos(game->ray.angle - game->player.angle); // fix the fisheye
	if (game->ray.wall_dist < 0.1)
		game->ray.wall_dist = 0.1;
	game->ray.wall_heigt = (TILE_SIZE / game->ray.wall_dist) * (WIN_WIDTH / 2) / tan(game->view.fov / 2);
	top_pix = (WIN_HEIGHT / 2) - (game->ray.wall_heigt / 2);
	bottom_pix = (WIN_HEIGHT / 2) + (game->ray.wall_heigt / 2);
	check_wall_dir(game, game->ray.h_inter, game->ray.v_inter);
	draw_wall(game, ray, top_pix, bottom_pix);
	draw_sky(game, ray, top_pix);
	draw_ground(game, ray, bottom_pix);
}

// rgb(234,182,118) //beige
// rgb(238,238,228) //grey
// rgb(25,118,162) //blue
// rgb(128,57,30) // brown