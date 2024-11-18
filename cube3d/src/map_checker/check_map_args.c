/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:03:52 by chris             #+#    #+#             */
/*   Updated: 2024/11/18 11:13:21 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


int	check_textures(int fd)
{
	int		i;
	int		texture_check;
	char	*line;
	
	texture_check = 0;

	while (line = get_next_line(fd) != NULL)
	{
		i = 0;
		if (ft_strncmp(line, "NO", 2) == 0)
			texture_check |= (1 << 0); // Set bit 0 for NO
		else if (ft_strncmp(line, "SO", 2) == 0)
			texture_check |= (1 << 1); // Set bit 1 for SO
		else if (ft_strncmp(line, "WE", 2) == 0)
			texture_check |= (1 << 2); // Set bit 2 for WE
		else if (ft_strncmp(line, "EA", 2) == 0)
			texture_check |= (1 << 3); // Set bit 3 for EA
		free(line);
	}
	if (texture_check != 15)
	{
		error("One mapfile is missing!");
		return (1);
	}
}

int check_map_args(int ac, char **av)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error("FD open failed.");
	check_textures(fd);
	check_floor_ceiling(fd);
	check_map(fd);
	close (fd);
	return (0);
}
