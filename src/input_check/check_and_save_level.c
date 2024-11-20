#include "../../include/cub3d.h"

int find_level_start(char **map)
{
    int i = 0;

    while (map[i])
    {
        if (ft_strchr(map[i], '1'))
            return i;
        i++;
    }
    return -1;
}

int find_level_end(char **map)
{
    int i = 0;

    while (map[i])
    {
        i++;
    }
    return i - 1;
}

int is_level_line(char *line)
{
    int i = 0;

    while (line[i] == ' ' || line[i] == '\t')
        i++;

    if (line[i] == '\0' || line[i] == '\n')
        return 0;

    while (line[i])
    {
        if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] != '\n')
            return 0;
        i++;
    }
    return 1;
}

int extract_level(char **map, char ***level, int level_start, int level_end)
{
    int i;
    int level_size = 0;

    i = level_start;
    while (i <= level_end)
    {
        if (is_level_line(map[i]))
            level_size++;
        i++;
    }

    *level = (char **)malloc(sizeof(char *) * (level_size + 1));
    if (!(*level))
        return 1;

    i = level_start;
    int j = 0;
    while (i <= level_end)
    {
        if (is_level_line(map[i]))
        {
            (*level)[j] = ft_strdup(map[i]);
            if (!(*level)[j])
            {
                while (j > 0)
                    free((*level)[--j]);
                free(*level);
                return 1;
            }
            j++;
        }
        i++;
    }

    (*level)[level_size] = NULL;
    return 0;
}

int check_and_save_level(t_map *map)
{
    int level_start = find_level_start(map->map);
    if (level_start == -1)
    {
        error("Error: No map found in map file.");
        return 1;
    }

    int level_end = find_level_end(map->map);

    if (extract_level(map->map, &map->level, level_start, level_end) != 0)
    {
        error("Error: Failed to extract the level data!");
        return 1;
    }

    int i = 0;
    while (map->level[i])
    {
        printf("Level line: %s", map->level[i]);
        i++;
    }

    return 0;
}
