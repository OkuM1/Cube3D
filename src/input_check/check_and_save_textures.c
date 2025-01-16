/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_save_textures.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:14:15 by chris             #+#    #+#             */
/*   Updated: 2025/01/16 18:23:44 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/cub3d.h"
/* 
void	skip_spaces(char **str)
{
	
	while (**str == ' ' || **str == '\t')
		*str += 1;
} */

int space_counter(char *str)
{
	int i;
	
	i = 0;
	while (str[i] == ' ' || str[i] == '\t') 
		i++;
	return (i);
}

char	*remove_newline(char *string)
{
	int i;

	i = 0;
	while (string[i] && string[i] != '\n')
		i++;
	
	if (string[i] == '\n')
		string [i] = '\0';
	return (string);
}

void save_texture(t_game *game, t_map *map)
{
	int	i;
	int	skip;
	
	i = 0;
	skip = 0;
	while (map->file[i])
	{
		skip = space_counter(map->file[i]);
		if (ft_strncmp(map->file[i] + skip, "NO", 2) == 0)
		{
			skip += 2 + space_counter(map->file[i] + skip + 2);
			game->map.n_text = remove_newline(ft_strdup(map->file[i] + skip));
		}
		else if (ft_strncmp(map->file[i] + skip, "SO", 2) == 0)
		{
			skip += 2 + space_counter(map->file[i] + skip + 2);
			game->map.s_text = remove_newline(ft_strdup(map->file[i] + skip));
		}
		else if (ft_strncmp(map->file[i] + skip, "WE", 2) == 0)
		{
			skip += 2 + space_counter(map->file[i] + skip + 2);
			game->map.w_text = remove_newline(ft_strdup(map->file[i] + skip));
		}
		else if (ft_strncmp(map->file[i] + skip, "EA", 2) == 0)
		{
			skip += 2 + space_counter(map->file[i] + skip + 2);
			game->map.e_text = remove_newline(ft_strdup(map->file[i] + skip));
		}
		i++;
	}
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
			texture_check |= (1 << 0); // Set bit 0 for NO
		else if (ft_strncmp(map->file[i] + skip, "SO", 2) == 0)
			texture_check |= (1 << 1); // Set bit 1 for SO
		else if (ft_strncmp(map->file[i] + skip, "WE", 2) == 0)
			texture_check |= (1 << 2); // Set bit 2 for WE
		else if (ft_strncmp(map->file[i] + skip, "EA", 2) == 0)
			texture_check |= (1 << 3); // Set bit 3 for EA
		i++;
	}
	if (texture_check != 15)
	{
		error("Error: One mapfile is missing!");
		return (1);
	}
	save_texture(game, map);
	return (0);
}
