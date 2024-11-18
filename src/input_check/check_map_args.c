/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:03:52 by chris             #+#    #+#             */
/*   Updated: 2024/11/18 19:04:06 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_arr_size_and_malloc(int fd, t_map *map)
{
	int		arr_size;
	char	*line;

	arr_size = 0;
	line = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		arr_size++;
		free(line);
	}
	map->map = (char **)malloc(sizeof(char *) * (arr_size + 1));
	if (!map->map)
	{
		error("Malloc failed for creating file_arr!");
		return (1);
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
		free(map->map);
		return (1);
	}
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		map->map[i] = line;
		i++;
	}
	map->map[i] = NULL;
	close (fd);
	return (0);
}

int check_and_save_map_args(char **av, t_game *game, t_map *map)
{
	if (av[1] == NULL)
		return (1);
	if (create_file_arr(av, map) == 1)
		return (1);
	if (check_and_save_textures(game, map) == 1)
		return (1);
	if ((check_and_save_floor(map)
		&& check_and_save_ceiling(map)) == 1)
		return (1);
	// if(check_map(file_arr))
		//save map
	return (0);
}
