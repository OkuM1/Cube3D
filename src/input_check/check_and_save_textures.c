/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_save_textures.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:14:15 by chris             #+#    #+#             */
/*   Updated: 2024/11/18 19:03:28 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/cub3d.h"

void save_texture(t_game *game, t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		if (ft_strncmp(map->map[i], "NO", 2) == 0)
			game->map.n_text = ft_strdup(map->map[i] + 3);
		else if (ft_strncmp(map->map[i], "SO", 2) == 0)
			game->map.s_text = ft_strdup(map->map[i] + 3);
		else if (ft_strncmp(map->map[i], "WE", 2) == 0)
			game->map.w_text = ft_strdup(map->map[i] + 3);
		else if (ft_strncmp(map->map[i], "EA", 2) == 0)
			game->map.e_text = ft_strdup(map->map[i] + 3);
		i++;
	}
}

int	check_and_save_textures(t_game *game, t_map *map)
{
	int		i;
	int		texture_check;
	
	i = 0;
	texture_check = 0;
	while (map->map[i])
	{
		if (ft_strncmp(map->map[i], "NO", 2) == 0)
			texture_check |= (1 << 0); // Set bit 0 for NO
		else if (ft_strncmp(map->map[i], "SO", 2) == 0)
			texture_check |= (1 << 1); // Set bit 1 for SO
		else if (ft_strncmp(map->map[i], "WE", 2) == 0)
			texture_check |= (1 << 2); // Set bit 2 for WE
		else if (ft_strncmp(map->map[i], "EA", 2) == 0)
			texture_check |= (1 << 3); // Set bit 3 for EA
		i++;
	}
	if (texture_check != 15) // 15 is 1111 in binary
	{
		error("Error: One mapfile is missing!");
		return (1);
	}
	save_texture(game, map);
	return (0);
}