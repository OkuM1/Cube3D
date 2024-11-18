/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:50:04 by chris             #+#    #+#             */
/*   Updated: 2024/11/18 10:15:35 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_input(int ac, char **av)
{
	int		fd;

	if (ac != 2)
	{
		ft_printf("[%d] = Invalid number of arguments!\n", ac);
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error("FD open failed.");
	close(fd);
	if (check_datatyp(av[1], ".cub") == 1)
	{
		ft_printf("Wrong Datatype! Datatype must be .cub\n");
		return (1);
	}
	return (0);
}

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
			return (1);
	}
	return (0);
}


