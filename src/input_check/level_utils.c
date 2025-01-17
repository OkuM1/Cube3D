/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:50:33 by mokutucu          #+#    #+#             */
/*   Updated: 2025/01/17 14:16:20 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	find_level_start(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (ft_strchr(map[i], '1'))
			return (i);
		i++;
	}
	return (-1);
}

int	find_level_end(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		i++;
	}
	return (i - 1);
}

int	is_level_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ' 
			&& line[i] != '\n' && line[i] != 'N' && line[i] != 'E'
			&& line[i] != 'S' && line[i] != 'W' && line[i] != '\0')
			return (0);
		i++;
	}
	return (1);
}
