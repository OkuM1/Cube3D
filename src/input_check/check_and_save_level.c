/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_save_level.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:46:03 by mokutucu          #+#    #+#             */
/*   Updated: 2025/01/17 14:12:08 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	count_level_lines(char **map, int start, int end)
{
	int	count;

	count = 0;
	while (start <= end)
	{
		if (is_level_line(map[start]))
			count++;
		start++;
	}
	return (count);
}

static int	copy_level_lines(char **map, char **level, int start, int end)
{
	int	index;

	index = 0;
	while (start <= end)
	{
		if (is_level_line(map[start]))
		{
			level[index] = ft_strdup(map[start]);
			if (!level[index])
			{
				while (index > 0)
					free(level[--index]);
				return (1);
			}
			index++;
		}
		start++;
	}
	level[index] = NULL;
	return (0);
}

int	extract_level(char **map, char ***level, int start, int end)
{
	int	level_size;

	level_size = count_level_lines(map, start, end);
	*level = (char **)malloc(sizeof(char *) * (level_size + 1));
	if (!*level)
		return (1);
	if (copy_level_lines(map, *level, start, end))
		return (1);
	return (0);
}

void	find_level_dimensions(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->level[i])
	{
		while (map->level[i][j] && map->level[i][j] != '\n')
			j++;
		i++;
	}
	map->level_height = i;
	map->level_width = j;
}

int	check_and_save_level(t_map *map)
{
	int	level_start;
	int	level_end;

	level_start = find_level_start(map->file);
	if (level_start == -1)
	{
		error("Error: No map found in map file.");
		return (1);
	}
	level_end = find_level_end(map->file);
	if (extract_level(map->file, &map->level, level_start, level_end) != 0)
	{
		error("Error: Failed to extract the level data!");
		return (1);
	}
	find_level_dimensions(map);
	return (0);
}
