/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:12:34 by mokutucu          #+#    #+#             */
/*   Updated: 2025/01/09 17:55:49 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// int get_color(t_game *game) // get the color of the wall
// {
// 	if (game->ray.wall_side == 'w')
// 		return (rgba_to_int(234,182,118,255)); // west wall
// 	else if (game->ray.wall_side == 'e')
// 		return (rgba_to_int(238,238,228,255)); // east wall
// 	if (game->ray.wall_side == 's')
// 		return (rgba_to_int(25,118,162,255)); // south wall
// 	else if (game->ray.wall_side == 'n')
// 		return (rgba_to_int(128,57,30,255)); // north wall
// 	return (0);
// }

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
	game->img.textures[0] = mlx_xpm_file_to_image(game->img.mlx, "textures/dark_texture.xpm", &game->img.tex_width, &game->img.tex_height);
	game->img.textures[1] = mlx_xpm_file_to_image(game->img.mlx, "textures/green_texture.xpm", &game->img.tex_width, &game->img.tex_height);
	game->img.textures[2] = mlx_xpm_file_to_image(game->img.mlx, "textures/orange_texture.xpm", &game->img.tex_width, &game->img.tex_height);
	game->img.textures[3] = mlx_xpm_file_to_image(game->img.mlx, "textures/purple_texture.xpm", &game->img.tex_width, &game->img.tex_height);
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

double texture_wall_hit(t_game *game)
{
	double wall_hit_x;

	if (game->ray.h_inter < game->ray.v_inter)
	{
		wall_hit_x = game->ray.hor_x / TILE_SIZE;
		wall_hit_x -= floor(wall_hit_x);
	}
	else if (game->ray.v_inter < game->ray.h_inter)
	{
		wall_hit_x = game->ray.vert_y / TILE_SIZE;
		wall_hit_x -= floor(wall_hit_x);
	}
	else
		wall_hit_x = 0;
	return wall_hit_x;
}

void draw_wall(t_game *game, int ray, int top_pix, int bottom_pix)
{
	int		y;
	int		tex_y;
	int		tex_x;
	char	*addr;
	void	*texture;
	int		bpp;
	int		line_length;
	int		endian;
	int		color;
	char	*pixel;
	
	y = top_pix;
	game->ray.wall_hit_x = texture_wall_hit(game);
	texture = get_texture(game);
	addr = mlx_get_data_addr(texture, &bpp, &line_length, &endian);
	tex_x = (int)(game->ray.wall_hit_x * game->img.tex_width) % game->img.tex_width;
	while (y < bottom_pix)
	{
		tex_y = ((y - top_pix) * game->img.tex_height) / (bottom_pix - top_pix);
		pixel = addr + (tex_y * line_length + tex_x * (bpp / 8));
		color = *(int *)pixel;
		my_mlx_pixel_put(game, ray, y, color);
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
	}
	else if (v_inter < h_inter)
	{
		if (game->ray.angle > M_PI / 2 && game->ray.angle < 3 * M_PI / 2)
			game->ray.wall_side = 'w';
		else
			game->ray.wall_side = 'e';
	}
}

void render_wall(t_game *game, int ray)
{
	double top_pix;
	double bottom_pix;

	top_pix = 0;
	bottom_pix = 0;
	game->ray.wall_dist *= cos(game->ray.angle - game->player.angle); // fix the fisheye
	game->ray.wall_heigt = (TILE_SIZE / game->ray.wall_dist) * ((WIN_WIDTH / 2) / tan(game->view.fov / 2)); // get the wall height
	top_pix = (WIN_HEIGHT / 2) - (game->ray.wall_heigt / 2); // get the top pixel
	bottom_pix = (WIN_HEIGHT / 2) + (game->ray.wall_heigt / 2); // get the bottom pixel
	if (top_pix < 0)
		top_pix = 0;
	if (bottom_pix > WIN_HEIGHT)
		bottom_pix = WIN_HEIGHT;
	check_wall_dir(game, game->ray.h_inter, game->ray.v_inter);
	draw_wall(game, ray, top_pix, bottom_pix);
	draw_sky(game, ray, top_pix);
	draw_ground(game, ray, bottom_pix);
}

// rgb(234,182,118) //beige
// rgb(238,238,228) //grey
// rgb(25,118,162) //blue
// rgb(128,57,30) // brown