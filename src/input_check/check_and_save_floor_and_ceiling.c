/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_save_floor_and_ceiling.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:22:06 by chris             #+#    #+#             */
/*   Updated: 2025/01/10 16:30:25 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void free_array(char **arr)
{
	int i = 0;

	if (!arr) 
		return;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int is_valid_digits(char *str)
{
	int i;
	
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

int rgba_to_int(int r, int g, int b, int a)
{
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

int validate_and_save_color(t_game *game, char *line, char identifier)
{
	char **nums;
	int i;
	int value;

	nums = ft_split(line + 2, ',');
	if (!nums)
	{
		error("Error: Failed to split color string.");
		free_array(nums);
		return (1);
	}
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
	if (identifier == 'F')
		game->map.floor_color = rgba_to_int(ft_atoi(nums[0]), ft_atoi(nums[1]), ft_atoi(nums[2]), 255);
	if (identifier == 'C')
		game->map.ceiling_color = rgba_to_int(ft_atoi(nums[0]), ft_atoi(nums[1]), ft_atoi(nums[2]), 255);
	free_array(nums);
	return (0);
}

int check_and_save_color(t_game *game, t_map *map, char identifier)
{
	int i;

	if (!map || !map->file)
	{
		error("Error: Null map structure!");
		return (1);
	}
	i = 0;
	while (map->file[i])
	{
		// Check if the line starts with the identifier F or C
		if (ft_strncmp(map->file[i], &identifier, 1) == 0)
		{
			return (validate_and_save_color(game, map->file[i], identifier));
		}
		i++;
	}
	return (1);
}
