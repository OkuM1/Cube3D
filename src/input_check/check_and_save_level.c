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

static int count_level_lines(char **map, int start, int end)
{
    int count = 0;
    while (start <= end)
    {
        if (is_level_line(map[start]))
            count++;
        start++;
    }
    return count;
}

static int copy_level_lines(char **map, char **level, int start, int end)
{
    int index = 0;
    while (start <= end)
    {
        if (is_level_line(map[start]))
        {
            level[index] = ft_strdup(map[start]);
            if (!level[index])
            {
                while (index > 0)
                    free(level[--index]);
                return 1;
            }
            index++;
        }
        start++;
    }
    level[index] = NULL;
    return 0;
}

int extract_level(char **map, char ***level, int start, int end)
{
    int level_size = count_level_lines(map, start, end);
    *level = (char **)malloc(sizeof(char *) * (level_size + 1));
    if (!*level)
        return 1;

    if (copy_level_lines(map, *level, start, end))
        return 1;

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
