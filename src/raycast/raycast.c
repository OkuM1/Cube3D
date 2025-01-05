

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

// Bresenham's line algorithm
void draw_line(t_game *game, int end_x, int end_y, int color)
{
	int err;
	int err2;
	int	current_x;
	int current_y;

	current_x = (int)game->player.x;
	current_y = (int)game->player.y;
	game->ray.delta_x = abs(end_x - current_x);
	game->ray.delta_y = abs(end_y - current_y);
	if (current_x < end_x) // Step direction for x
		game->ray.step_x = 1;
	else
		game->ray.step_x = -1;
	if (current_y < end_y) // Step direction for y
		game->ray.step_y = 1;
	else
		game->ray.step_y = -1;
	err = game->ray.delta_x - game->ray.delta_y;
	while (1)
	{
		my_mlx_pixel_put(game, current_x, current_y, color);
		if (current_x == end_x && current_y == end_y)
			break;
		err2 = 2 * err;
		if (err2 > -game->ray.delta_y)
		{
			err -= game->ray.delta_y;
			current_x += game->ray.step_x;
		}
		if (err2 < game->ray.delta_x)
		{
			err += game->ray.delta_x;
			current_y += game->ray.step_y;
		}
	}
}

int check_wall_hit(t_game *game, char c, double ray_y, double ray_x)
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

double get_h_inter(t_game *game)
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

double get_v_inter(t_game *game)
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

void draw_player_direction(t_game *game)
{
	double	current_angle;
	double	end_angle;
	double	end_x;
	double	end_y;
	double	h_inter;
	double	v_inter;

	end_y = 0;
	end_x = 0;
	h_inter = 0;
	v_inter = 0;
	game->ray.angle = game->player.angle - (game->view.fov / 2);
	current_angle = game->ray.angle;
	end_angle = game->player.angle + (game->view.fov / 2);
	while (current_angle <= end_angle)
	{
		game->ray.dir_x = cos(game->ray.angle);
		game->ray.dir_y = sin(game->ray.angle);
		h_inter = get_h_inter(game);
		v_inter = get_v_inter(game);
		printf("h_inter: %lf v_inter: %lf\n", h_inter, v_inter);
		if (h_inter < v_inter)
		{	
			end_x = game->ray.hor_x;
			end_y = game->ray.hor_y;
		}
		else if (v_inter < h_inter)
		{
			end_x = game->ray.vert_x;
			end_y = game->ray.vert_y;
		}
		printf("End X: %lf, End Y: %lf\n", end_x, end_y);
		draw_line(game, (int)end_x, (int)end_y, 0x00FF00);
		current_angle += deg_to_rad(0.5);
		game->ray.angle = current_angle;
		nor_angle(&game->ray.angle);
	}
}

void	draw_player(t_game *game)
{
	int	pl_size;
	int	x;
	int	y;

	pl_size = 8;
	y = game->player.y - pl_size / 2;
	while (y < game->player.y + pl_size / 2)
	{
		x = game->player.x - pl_size / 2;
		while (x < game->player.x + pl_size / 2)
		{
			my_mlx_pixel_put(game, x, y, PLAYER_COLOR);
			x++;
		}
		y++;
	}
}

void	draw_rectangle(t_game *game, int x_len, int y_len, unsigned int color)
{
	int	rect_x;
	int	rect_y;

	rect_y = y_len;
	while (rect_y < y_len + (TILE_SIZE -1))
	{
		rect_x = x_len;
		while (rect_x < x_len + (TILE_SIZE - 1))
		{
			my_mlx_pixel_put(game, rect_x, rect_y, color);
			rect_x++;
		}
		rect_y++;
	}
}

void	draw_map2d(t_game *game)
{
	int				y;
	int				x;
	int				x_len;
	int				y_len;
	unsigned int	color;

	y = 0;
	while (y < game->map.level_height)
	{
		x = 0;
		while (x < game->map.level_width)
		{	
			if (game->map.level[y][x] == '1')
				color = 0xFFFFFF;
			else
				color = 0x757575;
			x_len = x * TILE_SIZE;
			y_len = y * TILE_SIZE;
			draw_rectangle(game, x_len, y_len, color);
			x++;
		}
		y++;
	}
}

void	create_image(t_game *game)
{
	clear_image(game);
	draw_map2d(game);
	draw_player(game);
	draw_player_direction(game);
	mlx_put_image_to_window(game->img.mlx, game->img.mlx_win, game->img.img, 0, 0);
	// draw_rays(game);
}

// void	cast_ray(t_game *game, int *side)
// {
// 	double	pos_x;
// 	double	pos_y;

// 	pos_x = game->player.x;
// 	pos_y = game->player.y;
// 	calc_ray_params(game);
// 	check_raydirection(game, pos_x, pos_y);
// 	check_wallhit(game, pos_x, pos_y, side);
// }

// void	draw_rays(t_game *game)
// {
// 	int		ray;
// 	int		side;
// 	double	camera_x;
// 	double	hit_x;
// 	double	hit_y;
// 	// int		line_height;

// 	ray = 0;
// 	side = 0;
// 	// line_height = 0;
// 	camera_x = 0;
// 	// game->ray.plane_x = sin(game->player.angle) * 0.66; // Perpendicular to dirX
// 	// game->ray.plane_y = -cos(game->player.angle) * 0.66; // Perpendicular to dirY
// 	game->ray.angle = game->player.angle - M_PI / 6;
	
// 	while (ray < 20) // Cast one ray for each screen column
// 	{
// 		camera_x = 2 * ray / (double)WIN_WIDTH - 1; // Map ray index to camera plane
// 		game->ray.dir_x = cos(game->player.angle) + game->ray.plane_x * camera_x;
// 		game->ray.dir_y = sin(game->player.angle) + game->ray.plane_y * camera_x;

// 		// Draw rays as lines
// 		cast_ray(game, &side);

// 		hit_x = game->player.x + game->ray.dir_x * 500; // 500 is just the length of the ray
//         hit_y = game->player.y + game->ray.dir_y * 500;
// 		// if (side == 0)
// 		// 	line_height = (int)(WIN_HEIGHT / (game->ray.dir_x - game->player.x));
// 		// else
// 		// 	line_height = (int)(WIN_HEIGHT / (game->ray.dir_y - game->player.y));
// 		draw_line(game, (int)hit_x, (int)hit_y, 0xFF0000);
// 		game->ray.angle += deg_to_rad('3');
// 		ray++;
// 	}
// }
