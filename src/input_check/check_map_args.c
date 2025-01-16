/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:03:52 by chris             #+#    #+#             */
/*   Updated: 2025/01/16 18:54:08 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_arr_size_and_malloc(int fd, t_map *map)
{
	int		i;
	int		arr_size;
	char	*line;

	i = 0;
	arr_size = 0;
	line = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		arr_size++;
		free(line);
	}
	map->file = (char **)malloc(sizeof(char *) * (arr_size + 1));
	if (!map->file)
	{
		error("Malloc failed for creating file_arr!");
		return (1);
	}
	while (i <= arr_size)
	{
		map->file[i] = NULL;
		i++;
	}
	return (0);
}

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

int	create_file_arr(char **av, t_map *map)
{
	int		i;
	int		fd;
	char	*line;
	
	i = 0;
	fd = -1;
	line = NULL;
	if(open_fd(av, &fd) == 1)
		return (1);
	if (get_arr_size_and_malloc(fd, map) == 1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	if (open_fd(av, &fd) == 1)
	{
		free(map->file);
		return (1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		map->file[i] = line;
		if (!map->file[i])
		{
			free(line);
			while (i-- > 0)
				free(map->file[i]);
			free(map->file);
			close(fd);
			return (1);
		}
		// free(line);
		line = get_next_line(fd);
		i++;
	}
	map->file[i] = NULL;
	close(fd);
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

int check_and_save_map_args(char **av, t_game *game)
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
		return (1);;
	if(check_and_save_level(&game->map) == 1)
		return (1);
	return (0);
}
