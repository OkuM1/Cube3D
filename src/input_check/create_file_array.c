/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:19:14 by mokutucu          #+#    #+#             */
/*   Updated: 2025/01/17 14:14:12 by mokutucu         ###   ########.fr       */
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
	line = get_next_line(fd);
	while (line != NULL)
	{
		arr_size++;
		free(line);
		line = get_next_line(fd);
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

int	open_file_and_allocate(char **av, t_map *map)
{
	int	fd;

	fd = -1;
	if (open_fd(av, &fd) == 1)
		return (1);
	if (get_arr_size_and_malloc(fd, map) == 1)
	{
		close (fd);
		return (1);
	}
	close(fd);
	if (open_fd(av, &fd) == 1)
	{
		free(map->file);
		return (1);
	}
	return (fd);
}

int	read_lines_into_array(int fd, t_map *map)
{
	int		i;
	char	*line;

	i = 0;
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
		line = get_next_line(fd);
		i++;
	}
	map->file[i] = NULL;
	close(fd);
	return (0);
}

int	create_file_arr(char **av, t_map *map)
{
	int	fd;

	fd = open_file_and_allocate(av, map);
	if (fd == -1)
		return (1);
	if (read_lines_into_array(fd, map) == 1)
		return (1);
	return (0);
}
