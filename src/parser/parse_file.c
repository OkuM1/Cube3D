/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:08:43 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/18 19:03:22 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// void save_texture(char *line, t_game *game)
// {
// 	if (ft_strncmp(line, "NO", 2) == 0)
// 		game->map.N_text = ft_strdup(line + 3);
// 	else if (ft_strncmp(line, "SO", 2) == 0)
// 		game->map.S_text = ft_strdup(line + 3);
// 	else if (ft_strncmp(line, "WE", 2) == 0)
// 		game->map.W_text = ft_strdup(line + 3);
// 	else if (ft_strncmp(line, "EA", 2) == 0)
// 		game->map.E_text = ft_strdup(line + 3);
// }

// void save_color(char *line, t_game *game)
// {
// 	char **nums;
// 	int	 i;
		
// 	nums = ft_split((line + 2), ',');
// 	if (!nums)
// 		error("nums no space");
// 	i = 0;
// 	while (nums[i] != NULL && i < 3)
// 	{
// 		if (ft_strncmp(line, "F", 1) == 0)
// 			game->map.floor_color[i] = ft_atoi(nums[i]);
// 		else
// 			game->map.ceiling_color[i] = ft_atoi(nums[i]);
// 		i++;
// 	}
		
// }

// void	save_map(int fd, char *line, t_game *game)
// {
		
// }
void	handle_map(int fd, char *line, t_game *game)
{
	// int i;
	int size;
	char *tmp;
		
	size = 0;
	while ((tmp = get_next_line(fd)) != NULL)
	{
		size++;
		free (tmp);
	}

	game->map.map = malloc(sizeof(char *) * size);
	if (line)
		free (line);
	// save_map(fd, line, game);
}

int parse_file(char **av, t_game *game)
{
	int fd;
	char *line;
		
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error("FD open failed.");
	while ((line = get_next_line(fd)) != NULL)
	{
		int i = 0;

		// whitespaces
		while (line[i] == ' ' || line[i] == '\t')
			i++;

		// empty lines
		if (line[i] == '\0')
		{
			free(line);
			continue;
		}
		// // Handle textures
		// if (ft_strncmp(&line[i], "NO", 2) == 0 || ft_strncmp(&line[i], "SO", 2) == 0 ||
		// 	ft_strncmp(&line[i], "WE", 2) == 0 || ft_strncmp(&line[i], "EA", 2) == 0)
		// {
		// 	printf("Texture identifier found: %s\n", &line[i]);
		// 	save_texture(&line[i], game);
		// }
		// // Handle colors
		// else if (ft_strncmp(&line[i], "F", 1) == 0 || ft_strncmp(&line[i], "C", 1) == 0)
		// {
		// 	printf("Color identifier found: %s\n", &line[i]);
		// 	save_color(&line[i], game);
		// }
		// Handle map start
		else if (line[i] == '1')
		{
			printf("Map starts here: %s\n", &line[i]);
			handle_map(fd, &line[i], game);
			break;
		}
		else
		{
			printf("Empty line -> %s\n", &line[i]);
		}

		free(line);
	}
	close(fd);
	return 0;
}
