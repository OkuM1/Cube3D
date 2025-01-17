/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_save_floor_and_ceiling.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:22:06 by chris             #+#    #+#             */
/*   Updated: 2025/01/17 14:22:08 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_valid_digits(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	process_colors(t_game *game, char **nums, char identifier)
{
	if (identifier == 'F')
		game->map.floor_color = rgba_int(ft_atoi(nums[0]), 
				ft_atoi(nums[1]), ft_atoi(nums[2]), 255);
	else if (identifier == 'C')
		game->map.ceiling_color = rgba_int(ft_atoi(nums[0]), 
				ft_atoi(nums[1]), ft_atoi(nums[2]), 255);
}

int	handle_split_error(char **nums)
{
	if (!nums)
	{
		error("Error: Failed to split color string.");
		free_array(nums);
		return (1);
	}
	return (0);
}

int	val_save_color(t_game *game, char *line, char identifier)
{
	char	**nums;
	int		i;
	int		value;

	nums = ft_split(line, ',');
	handle_split_error(nums);
	i = 0;
	while (nums[i] && i < 3)
	{
		value = ft_atoi(nums[i]);
		if (value < 0 || value > 255)
		{
			error("RGB value is out of range (0-255)!");
			free_array(nums);
			return (1);
		}
		i++;
	}
	process_colors(game, nums, identifier);
	free_array(nums);
	return (0);
}

int	check_and_save_color(t_game *game, t_map *map, char identifier)
{
	int	i;
	int	skip;

	if (!map || !map->file)
	{
		error("Error: Null map structure!");
		return (1);
	}
	i = 0;
	while (map->file[i])
	{
		skip = 0;
		skip = space_counter(map->file[i]);
		if (ft_strncmp(map->file[i] + skip, &identifier, 1) == 0)
		{
			skip += 1 + space_counter(map->file[i] + skip + 1);
			return (val_save_color(game, map->file[i] + skip, identifier));
		}
		i++;
	}
	return (1);
}
