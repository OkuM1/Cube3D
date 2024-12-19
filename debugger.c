#include "include/cub3d.h"

void print_img(t_game *game) {
    t_img *img = &game->img;
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

void print_ray(t_game *game) {
    t_ray *ray = &game->ray;
    printf("\n--- RAY ---\n");
    printf("ray_angle: %f\n", ray->ray_angle);
    printf("wall_dist: %f\n", ray->wall_dist);
    // printf("hor_x: %f\n", ray->hor_x);
    // printf("hor_y: %f\n", ray->hor_y);
    // printf("vert_x: %f\n", ray->vert_x);
    // printf("vert_y: %f\n", ray->vert_y);
    printf("wall_flag: %d\n", ray->wall_flag);
}

void print_view(t_game *game) {
    t_view *view = &game->view;
    printf("\n--- VIEW ---\n");
    printf("fov: %f\n", view->fov);
    printf("x: %f\n", view->x);
    printf("y: %f\n", view->y);
    printf("height: %d\n", view->height);
    printf("width: %d\n", view->width);
    printf("zoom: %f\n", view->zoom);
}

void print_map(t_game *game) {
    t_map *map = &game->map;
    printf("\n--- MAP ---\n");
    printf("map_size: %d\n", map->map_size);
    printf("n_text: %s\n", map->n_text);
    printf("s_text: %s\n", map->s_text);
    printf("w_text: %s\n", map->w_text);
    printf("e_text: %s\n", map->e_text);
    printf("floor_color: [%d, %d, %d]\n", map->floor_color[0], map->floor_color[1], map->floor_color[2]);
    printf("ceiling_color: [%d, %d, %d]\n", map->ceiling_color[0], map->ceiling_color[1], map->ceiling_color[2]);
    printf("level_height: %d\n", map->level_height);
    printf("level_width: %d\n", map->level_width);
    for (int i = 0; i < map->level_height; i++) {
        printf("level[%d]: %s\n", i, map->level[i]);
    }
}

void print_player(t_game *game) {
    t_player *player = &game->player;
    printf("\n--- PLAYER ---\n");
    printf("player_id: %d\n", player->player_id);
    printf("x: %d\n", player->x);
    printf("y: %d\n", player->y);
    printf("player_angle: %f\n", player->player_angle);
    printf("move_speed: %f\n", player->move_speed);
    printf("rotation_speed: %f\n", player->rotation_speed);
    printf("l_r: %d\n", player->l_r);
    printf("u_d: %d\n", player->u_d);
    printf("rot: %d\n", player->rot);
}

// void print_game(t_game *game) {
//     printf("\n--- GAME ---\n");
//     print_view(game);
//     print_img(game);
//     print_map(game);
//     print_player(game);
//     print_ray(game);
// }

void	debugger(t_game *game, char *struct_name)
{
	if (ft_strcmp("img", struct_name) == 0)
		print_img(game);
	else if (ft_strcmp("ray", struct_name) == 0)
		print_ray(game);
	else if (ft_strcmp("view", struct_name) == 0)
		print_view(game);
	else if (ft_strcmp("map", struct_name) == 0)
		print_map(game);
	else if (ft_strcmp("player", struct_name) == 0)
		print_player(game);
}