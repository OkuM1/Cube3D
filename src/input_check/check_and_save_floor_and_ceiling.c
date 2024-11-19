/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_save_floor_and_ceiling.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:22:06 by chris             #+#    #+#             */
/*   Updated: 2024/11/19 14:35:14 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void free_array(char **arr)
{
    int i;

    if (!arr) // Check for null pointer
        return;

    i = 0;
    while (arr[i])
    {
        free(arr[i]); // Free each string
        i++;
    }
    free(arr); // Free the array itself
}

void save_color(t_game *game, t_map *map, int index)
{
    char **nums;
    int  i;

    nums = ft_split((map->map[index] + 2), ',');
    if (!nums)
    {
        error("Memory allocation failed for RGB values.");
        return;
    }

    // Validate the number of RGB components
    i = 0;
    while (nums[i])
        i++;
    if (i != 3)
    {
        error("Invalid RGB format: requires 3 components.");
        free_array(nums);
        return;
    }

    // Assign colors to floor or ceiling
    i = 0;
    while (i < 3)
    {
        if (ft_strncmp(map->map[index], "F", 1) == 0)
            game->map.floor_color[i] = ft_atoi(nums[i]);
        else
            game->map.ceiling_color[i] = ft_atoi(nums[i]);
        i++;
    }

    free_array(nums);
}



int	check_RGB_values(t_map *map, int *i)
{
	int value;
	int	j;

	value = 0;
	j = 0;
	while (map->map[*i][j] == ' ')
		j++;
	while (ft_isdigit(map->map[*i][j]))
	{
		value = value * 10 + (map->map[*i][j] - '0');
		if (value > 255)
		{
			error("Floor or ceiling value is out of RGB Range!");
			return (1);
		}
		j++;
	}
	while (map->map[*i][j] == ' ' || map->map[*i][j] == ',')
		j++;
		
	*i += 1;
	return (0);
}

int	check_and_save_ceiling(t_game *game, t_map *map)
{
	int		i;
	int		C_found;
	
	C_found = 0;
	i = 0;
	while (map->map[i])
	{
		if (ft_strncmp(map->map[i], "C ", 2) == 0)
		{
			i = 2;
			while (map->map[i])
			{
				if (check_RGB_values(map, &i) == 1)
				{
					error ("Error: Wrong value for ceiling!");
					return (1);
				}
				save_color(game, map, i);
				C_found = 1;
				break;
			}
		}
		i++;
	}
	if (C_found == 0)
		return (1);
	return (0);
}

int	check_and_save_floor(t_game *game, t_map *map)
{
	int		i;
	int		F_found;
	
	F_found = 0;
	i = 0;
	while (map->map[i])
	{
		if (ft_strncmp(map->map[i], "F ", 2) == 0)
		{
			i = 2;
			while (map->map[i])
			{
				if (check_RGB_values(map, &i) == 1)
				{
					error ("Error: Wrong value for floor!");
					return (1);
				}
				save_color(game, map, i);
				F_found = 1;
				break;
			}
		}
		i++;
	}
	if (F_found == 0)
		return (1);
	return (0);
}
