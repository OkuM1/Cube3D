/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_save_floor_and_ceiling.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:22:06 by chris             #+#    #+#             */
/*   Updated: 2024/11/18 19:03:38 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void save_color(t_game *game, t_map *map)
{
	char **nums;
	int	 i;

	i = 0;
	nums = ft_split((map->map[i] + 2), ',');
	if (!nums)
		error("nums no space");
	while (nums[i] != NULL && i < 3)
	{
		if (ft_strncmp(map->map[i], "F", 1) == 0)
			game->map.floor_color[i] = ft_atoi(nums[i]);
		else
			game->map.ceiling_color[i] = ft_atoi(nums[i]);
		i++;
	}
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
	return (0);
}

int	check_and_save_ceiling(t_map *map)
{
	int		i;
	int		C_found;
	
	C_found = 0;
	while (map->map[i])
	{
		if (strncmp(map->map[i], "C ", 2) == 0)
		{
			i = 2;
			while (map->map[i])
			{
				if (check_RGB_values(map, &i) == 1)
				{
					error ("Error: Wrong value for ceiling!");
					return (1);
				}
			}
			C_found = 1;
		}
		i++;
	}
	if (C_found == 0)
		return (1);
	return (0);
}

int	check_and_save_floor(t_map *map)
{
	int		i;
	int		F_found;
	
	F_found = 0;
	while (map->map[i])
	{
		if (strncmp(map->map[i], "F ", 2) == 0)
		{
			i = 2;
			while (map->map[i])
			{
				if (check_RGB_values(map, &i) == 1)
				{
					error ("Error: Wrong value for floor!");
					return (1);
				}
			}
			F_found = 1;
		}
		i++;
	}
	if (F_found == 0)
		return (1);
	return (0);
}
