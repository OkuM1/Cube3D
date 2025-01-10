

#include "../../include/cub3d.h"

void	clear_image(t_game *game)
{
	int		i;
	int		total_pixels;
	char	*pixel_buffer;

	i = 0;
	total_pixels = WIN_WIDTH * WIN_HEIGHT;
	pixel_buffer = game->img.img_address;
	while (i < total_pixels)
	{
		*(unsigned int *)pixel_buffer = 0x000000;
		pixel_buffer += (game->img.bpp / 8);
		i++;
	}
}

// transfers degree to radians
double	deg_to_rad(double a)
{
	return (a * M_PI / 180);
}

// normalize the angle
void nor_angle(double *angle)
{
	while (*angle < 0)
		*angle += 2 * M_PI;
	while (*angle > 2 * M_PI)
		*angle -= 2 * M_PI;
}

int	check_wall_hit(t_game *game, char c, double ray_y, double ray_x)
{
	int	map_x;
	int	map_y;

	if (c == 'h')
	{
		map_x = (int)ray_x / TILE_SIZE;
		if (game->ray.dir_y < 0)
			map_y = (int)((ray_y - 10) / TILE_SIZE);
		else
			map_y = (int)(ray_y + 10) / TILE_SIZE;
	}
	else if (c == 'v')
	{
		map_y = (int)ray_y / TILE_SIZE;
		if (game->ray.dir_x < 0)
			map_x = (int)((ray_x - 10) / TILE_SIZE);
		else
			map_x = (int)(ray_x + 10) / TILE_SIZE;
	}
	else
		return (0);
	if (map_x < 0 || map_y < 0
		|| map_x >= game->map.level_width || map_y >= game->map.level_height
		|| game->map.level[map_y][map_x] == '1')
		return (1);
	return (0);
}

double	get_h_inter(t_game *game)
{
	if (game->ray.dir_y < 0)
	{
		game->ray.hor_y = floor(game->player.y / TILE_SIZE) * TILE_SIZE;
		game->ray.step_y = -TILE_SIZE;
	}
	else
	{
		game->ray.hor_y = floor(game->player.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		game->ray.step_y = TILE_SIZE;
	}
	game->ray.hor_x = game->player.x + (game->ray.hor_y - game->player.y) * (game->ray.dir_x / game->ray.dir_y);
	while (1)
	{
		if (check_wall_hit(game, 'h', game->ray.hor_y, game->ray.hor_x) == 1)
			break ;
		game->ray.hor_y += game->ray.step_y;
    	game->ray.hor_x += game->ray.step_y * (game->ray.dir_x / game->ray.dir_y);
		if (game->ray.hor_x < 0 || game->ray.hor_x >= game->map.level_width * TILE_SIZE
			|| game->ray.hor_y < 0 || game->ray.hor_y >= game->map.level_height * TILE_SIZE)
			return (HUGE_VAL);
	}
	return (sqrt(pow(game->ray.hor_x - game->player.x, 2) + pow(game->ray.hor_y - game->player.y, 2))); // get the distance
}

double	get_v_inter(t_game *game)
{
	if (game->ray.dir_x < 0)
	{
		game->ray.vert_x = floor(game->player.x / TILE_SIZE) * TILE_SIZE;
		game->ray.step_x = -TILE_SIZE;
	}
	else
	{
		game->ray.vert_x = floor(game->player.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		game->ray.step_x = TILE_SIZE;
	}
	game->ray.vert_y = game->player.y + (game->ray.vert_x - game->player.x) * (game->ray.dir_y / game->ray.dir_x);
	while (1)
	{
		if (check_wall_hit(game, 'v', game->ray.vert_y, game->ray.vert_x) == 1)
			break ;
		game->ray.vert_x += game->ray.step_x;
		game->ray.vert_y += game->ray.step_x * (game->ray.dir_y / game->ray.dir_x);
		if (game->ray.vert_x < 0 || game->ray.vert_x >= game->map.level_width * TILE_SIZE
			|| game->ray.vert_y < 0 || game->ray.vert_y >= game->map.level_height * TILE_SIZE)
			return (HUGE_VAL) ;
	}
	return (sqrt(pow(game->ray.vert_x - game->player.x, 2) + pow(game->ray.vert_y - game->player.y, 2))); // get the distance
}

void	cast_rays(t_game *game)
{
	int		ray;
	double	current_angle;

	ray = 0;
	game->ray.angle = game->player.angle - (game->view.fov / 2);
	current_angle = game->ray.angle;
	while (ray < game->view.width) // Cast one ray for each screen column
	{
		game->ray.dir_x = cos(current_angle);
		game->ray.dir_y = sin(current_angle);
		game->ray.h_inter = get_h_inter(game);
		game->ray.v_inter = get_v_inter(game);
		if (game->ray.v_inter < game->ray.h_inter)
			game->ray.wall_dist = game->ray.v_inter;
		else if (game->ray.h_inter < game->ray.v_inter)
			game->ray.wall_dist = game->ray.h_inter;		
		game->ray.angle = current_angle;
		nor_angle(&game->ray.angle);
		render_wall(game, ray);
		current_angle += (game->view.fov / game->view.width);
		ray++;
	}
}

void	create_image(t_game *game)
{
	clear_image(game);
	cast_rays(game);
	// if (game->player.key_m == 1)
	// {
		// create_minimap(game);
	// }
	// mlx_put_image_to_window(game->img.mlx, game->img.mlx_win, game->img.img, 0, 0);
}
