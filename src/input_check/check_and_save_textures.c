/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_save_textures.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:14:15 by chris             #+#    #+#             */
/*   Updated: 2025/01/17 14:12:44 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	process_texture(char **texture, char *line, int skip)
{
	skip += 2 + space_counter(line + skip + 2);
	*texture = remove_newline(ft_strdup(line + skip));
}

void	save_texture(t_game *game, t_map *map)
{
	int	i;
	int	skip;

	i = 0;
	while (map->file[i])
	{
		skip = space_counter(map->file[i]);
		if (ft_strncmp(map->file[i] + skip, "NO", 2) == 0)
			process_texture(&game->map.n_text, map->file[i], skip);
		else if (ft_strncmp(map->file[i] + skip, "SO", 2) == 0)
			process_texture(&game->map.s_text, map->file[i], skip);
		else if (ft_strncmp(map->file[i] + skip, "WE", 2) == 0)
			process_texture(&game->map.w_text, map->file[i], skip);
		else if (ft_strncmp(map->file[i] + skip, "EA", 2) == 0)
			process_texture(&game->map.e_text, map->file[i], skip);
		i++;
	}
}

int	texture_missing(int a)
{
	if (a != 15)
	{
		error("Error: One mapfile is missing!");
		return (1);
	}
	return (0);
}

int	check_and_save_textures(t_game *game, t_map *map)
{
	int		i;
	int		texture_check;
	int		skip;

	i = 0;
	texture_check = 0;
	while (map->file[i])
	{
		skip = 0;
		skip = space_counter(map->file[i]);
		if (ft_strncmp(map->file[i] + skip, "NO", 2) == 0)
			texture_check |= (1 << 0);
		else if (ft_strncmp(map->file[i] + skip, "SO", 2) == 0)
			texture_check |= (1 << 1);
		else if (ft_strncmp(map->file[i] + skip, "WE", 2) == 0)
			texture_check |= (1 << 2);
		else if (ft_strncmp(map->file[i] + skip, "EA", 2) == 0)
			texture_check |= (1 << 3);
		i++;
	}
	if (texture_missing(texture_check) != 0)
		return (1);
	save_texture(game, map);
	return (0);
}
