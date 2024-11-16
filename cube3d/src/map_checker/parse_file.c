/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:08:43 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/16 21:12:17 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int parse_file(char **av, t_game *game)
{
    (void) game;
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

        // Handle textures
        if (ft_strncmp(&line[i], "NO", 2) == 0 || ft_strncmp(&line[i], "SO", 2) == 0 ||
            ft_strncmp(&line[i], "WE", 2) == 0 || ft_strncmp(&line[i], "EA", 2) == 0)
        {
            printf("Texture identifier found: %s\n", &line[i]);
        }
        // Handle colors
        else if (ft_strncmp(&line[i], "F", 1) == 0 || ft_strncmp(&line[i], "C", 1) == 0)
        {
            printf("Color identifier found: %s\n", &line[i]);
        }
        // Handle map start
        else if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S' ||
                line[i] == 'E' || line[i] == 'W')
        {
            printf("Map starts here: %s\n", &line[i]);
            break;  // Exit since map is the last section
        }
        else
        {
            printf("Error: Invalid line format -> %s\n", &line[i]);
        }

        free(line);
    }

    close(fd);
    return 0;
}
