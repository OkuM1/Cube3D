/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:03:52 by chris             #+#    #+#             */
/*   Updated: 2024/11/18 15:41:48 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_RGB_values(char *line, int *i)
{
	int value;

	value = 0;
	while (line[*i] == ' ')
		(*i)++;
	while (ft_isdigit(line[*i]))
	{
		value = value * 10 + (line[*i] - '0');
		if (value > 255)
		{
			error("Floor or ceiling value is out of RGB Range!");
			return (1);
		}
		(*i)++;
	}
	while (line[*i] == ' ' || line[*i] == ',')
		(*i)++;
	return (0);
}

int	check_ceiling(int fd)
{
	int		i;
	int		C_found;
	char	*line;
	
	C_found = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (strncmp(line, "C ", 2) == 0)
		{
			i = 2;
			while (line[i])
			{
				if (check_RGB_values(line, &i) == 1)
				{
					error ("Error: Wrong value for ceiling!");
					return (1);
				}
			}
			C_found = 1;
		}
		free(line);
	}
	if (C_found == 0)
		return (1);
	return (0);
}

int	check_floor(int ac, char **av)
{
	int		i;
	int		fd;
	int		F_found;
	char	*line;
	
	F_found = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Read line: '%s'\n", line);
		if (strncmp(line, "F ", 2) == 0)
		{
			i = 2;
			while (line[i])
			{
				if (check_RGB_values(line, &i) == 1)
				{
					error ("Error: Wrong value for floor!");
					return (1);
				}
			}
			F_found = 1;
		}
		free(line);
	}
	if (F_found == 0)
		return (1);
	return (0);
}

int	check_textures(int fd)
{
	int		texture_check;
	char	*line;
	
	texture_check = 0;

	while ((line = get_next_line(fd)) != NULL)
	{
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
	if (texture_check != 15) // 15 is 1111 in binary
	{
		error("Error: One mapfile is missing!");
		return (1);
	}
	return (0);
}

int	create_file_arr(char ***file_arr, int fd)
{
	
}

int check_map_args(int fd)
{
	char **file_arr;

	file_arr = NULL;
	create_file_arr(file_arr, fd);
	if (check_textures(fd))
		//save textures
	if (check_floor(fd) && check_ceiling(fd))
		//save floor and ceiling
	// if(check_map(fd))
		//save map
	{
		close (fd);
		return (1);
	}

	close (fd);
	return (0);
}
