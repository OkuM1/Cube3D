/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:50:04 by chris             #+#    #+#             */
/*   Updated: 2025/01/17 16:08:23 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_datatyp(char *file_name, char *datatype)
{
	int	i;
	int	file_len;
	int	datatype_len;

	i = 0;
	file_len = ft_strlen(file_name);
	datatype_len = ft_strlen(datatype);
	while (datatype_len != 0)
	{
		if (file_name[file_len - datatype_len] == datatype[i])
		{
			datatype_len--;
			i++;
		}
		else
		{
			ft_printf("Error: Wrong Datatype! Datatype must be .cub\n");
			return (1);
		}
	}
	return (0);
}

void	copy_level(t_game *game, char ***map)
{
	int		i;

	i = 0;
	*map = (char **)malloc(sizeof(char *) * (game->map.level_height + 1));
	if (!(*map))
	{
		error("Malloc failed for creating file_arr!");
		return ;
	}
	while (game->map.level[i] != NULL)
	{
		(*map)[i] = ft_strdup(game->map.level[i]);
		i++;
	}
	(*map)[i] = NULL;
}

int	flood_check(t_game *game, char ***map, int y, int x)
{
	if (y < 0 || y >= game->map.level_height || x < 0 
		|| x >= game->map.level_width)
		return (1);
	if ((*map)[y][x] == '0' || (*map)[y][x] == 'N' 
		|| (*map)[y][x] == 'E' || (*map)[y][x] == 'W' || (*map)[y][x] == 'S')
	{
		(*map)[y][x] = 'F';
		if (flood_check(game, map, y - 1, x) == 1)
			return (1);
		if (flood_check(game, map, y + 1, x) == 1)
			return (1);
		if (flood_check(game, map, y, x - 1) == 1)
			return (1);
		if (flood_check(game, map, y, x + 1) == 1)
			return (1);
	}
	if ((*map)[y][x] == '\n' || (*map)[y][x] == '\0' || (*map)[y][x] == ' ')
		return (1);
	return (0);
}

int	check_input(int ac, char **av, t_game *game)
{
	char	**map;

	map = NULL;
	if (ac != 2)
	{
		ft_printf("[%d] = Invalid number of arguments!\n", ac);
		return (1);
	}
	if (check_datatyp(av[1], ".cub") == 1)
		return (1);
	if (check_and_save_map_args(av, game) == 1)
		return (1);
	if (find_player_start(game) == 1)
		return (1);
	copy_level(game, &map);
	if (flood_check(game, &map, game->player.y_grid, game->player.x_grid) == 1)
		return (1);
	free_array(map);
	return (0);
}
