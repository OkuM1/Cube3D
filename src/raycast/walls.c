/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:12:34 by mokutucu          #+#    #+#             */
/*   Updated: 2025/01/09 16:05:33 by cwick            ###   ########.fr       */
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

void	get_texture(t_game *game) // get the color of the wall
{
	int		width;
	int		height;

	game->img.img_texture = mlx_xpm_file_to_image(game->img.mlx, "textures/green_texture.xpm", &width, &height);
	// if (game->ray.wall_side == 'w')
	// 	game->img.img_texture = mlx_xpm_file_to_image(game->img.mlx, "textures/dark_texture.xpm", &width, &height);
	// else if (game->ray.wall_side == 'e')
	// 	game->img.img_texture = mlx_xpm_file_to_image(game->img.mlx, "textures/green_texture.xpm", &width, &height);
	// else if (game->ray.wall_side == 's')
	// 	game->img.img_texture = mlx_xpm_file_to_image(game->img.mlx, "textures/orange_texture.xpm", &width, &height);
	// else if (game->ray.wall_side == 'n')
	// 	game->img.img_texture = mlx_xpm_file_to_image(game->img.mlx, "textures/purple_texture.xpm", &width, &height);
	if (!game->img.img)
	{
	    printf("No texture found!\n");
	}
}

void draw_wall(t_game *game, int ray, int top_pix, int bottom_pix)
{
	// unsigned int	color;
	int		y;
	int		x;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		color;
	char	*pixel;
	
	y = top_pix;
	x = 0;
	// color = get_color(game);
	get_texture(game);
	addr = mlx_get_data_addr(game->img.img_texture, &bpp, &line_length, &endian);
	if (y < bottom_pix)
	{
		while (y < bottom_pix)
		{
			pixel = addr + (y * line_length + x * (bpp / 8));
			color = *(int *)pixel;
			my_mlx_pixel_put(game, ray, y, color);
			y++;
			x++;
		}
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

void render_wall(t_game *game, int ray, double h_inter, double v_inter)
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
	check_wall_dir(game, h_inter, v_inter);
	// get_texture(game);
	draw_wall(game, ray, top_pix, bottom_pix);
	draw_sky(game, ray, top_pix);
	draw_ground(game, ray, bottom_pix);
}

// rgb(234,182,118) //beige
// rgb(238,238,228) //grey
// rgb(25,118,162) //blue
// rgb(128,57,30) // brown