/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:03:52 by chris             #+#    #+#             */
/*   Updated: 2025/01/17 13:45:37 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	open_fd(char **av, int *fd)
{
	*fd = open(av[1], O_RDONLY);
	if (*fd < 0)
	{
		error("FD open failed.");
		return (1);
	}
	return (0);
}

int	check_texture_file(t_game *game)
{
	int	fd;

	fd = -1;
	fd = open(game->map.n_text, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(game->map.s_text, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(game->map.w_text, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(game->map.e_text, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

int	check_and_save_map_args(char **av, t_game *game)
{
	if (av[1] == NULL)
		return (1);
	if (create_file_arr(av, &game->map) == 1)
		return (1);
	if (check_and_save_textures(game, &game->map) == 1)
		return (1);
	if (check_texture_file(game) == 1)
		return (1);
	if (check_and_save_color(game, &game->map, 'F') == 1)
		return (1);
	if (check_and_save_color(game, &game->map, 'C') == 1)
		return (1);
	if (check_and_save_level(&game->map) == 1)
		return (1);
	return (0);
}
