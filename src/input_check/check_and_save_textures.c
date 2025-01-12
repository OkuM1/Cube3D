/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_save_textures.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:14:15 by chris             #+#    #+#             */
/*   Updated: 2025/01/12 15:00:23 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/cub3d.h"

void	skip_spaces(char **str)
{
	while (**str == ' ' || **str == '\t')
		*str += 1;
}

char	*remove_newline(char *string)
{
	int i;

	i = 0;
	while (string[i] != '\n')
		i++;
	
	if (string[i] == '\n')
		string [i] = '\0';
	return (string);
}

void save_texture(t_game *game, t_map *map)
{
	int	i;

	i = 0;
	while (map->file[i])
	{
		skip_spaces(&map->file[i]);
		if (ft_strncmp(map->file[i], "NO", 2) == 0)
		{
			map->file[i] += 2;
			skip_spaces(&map->file[i]);
			game->map.n_text = remove_newline(ft_strdup(map->file[i]));

		}
		else if (ft_strncmp(map->file[i], "SO", 2) == 0)
		{
			map->file[i] += 2;
			skip_spaces(&map->file[i]);
			game->map.s_text = remove_newline(ft_strdup(map->file[i]));
		}
		else if (ft_strncmp(map->file[i], "WE", 2) == 0)
		{
			map->file[i] += 2;
			skip_spaces(&map->file[i]);
			game->map.w_text = remove_newline(ft_strdup(map->file[i]));
		}
		else if (ft_strncmp(map->file[i], "EA", 2) == 0)
		{
			map->file[i] += 2;
			skip_spaces(&map->file[i]);
			game->map.e_text = remove_newline(ft_strdup(map->file[i]));
		}
		i++;
	}
}

int	check_and_save_textures(t_game *game, t_map *map)
{
	int		i;
	int		texture_check;
	
	i = 0;
	texture_check = 0;
	while (map->file[i])
	{
		skip_spaces (&map->file[i]);
		if (ft_strncmp(map->file[i], "NO", 2) == 0)
			texture_check |= (1 << 0); // Set bit 0 for NO
		else if (ft_strncmp(map->file[i], "SO", 2) == 0)
			texture_check |= (1 << 1); // Set bit 1 for SO
		else if (ft_strncmp(map->file[i], "WE", 2) == 0)
			texture_check |= (1 << 2); // Set bit 2 for WE
		else if (ft_strncmp(map->file[i], "EA", 2) == 0)
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
