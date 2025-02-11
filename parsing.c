/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:58:31 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/02/10 23:02:41 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_lines(char *filename)
{
	int		count;
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return -1;
	line = get_next_line(fd);
	count = 0;
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

t_map	*read_map(char *filename)
{
	char *line;
	int	fd;
	t_map	*map_data;
	int	i;
	int	lines;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	lines = count_lines(filename);
	map_data = malloc(sizeof(t_map));
	if (!map_data)
		return (NULL);
	map_data->map = malloc((lines + 1) * sizeof(char *));
	if (!map_data->map)
	{
		free(map_data);
		return (NULL);
	}
	map_data->height = lines;
	i = 0;
	line = get_next_line(fd);
	if (!line)
	{
		free(map_data->map);
		free(map_data);
		close(fd);
		return (NULL);
	}
	char *newline = strchr(line, '\n');
    if (newline)
        *newline = '\0';
    map_data->width = strlen(line); 
	while (line)
	{
		newline = strchr(line, '\n');
        if (newline)
            *newline = '\0';
		map_data->map[i] = strdup(line);
		if (!map_data->map[i])
		{
			while (i-- >= 0)
				free(map_data->map[i]);
			free(map_data->map);
			free(map_data);
			free(line);
			close(fd);
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	map_data->map[i] = NULL;
	close(fd);
	return (map_data);
}

int	is_rectangular(t_map *map)
{
	int	i;

	if (!map || !map->map || !map->map[0])
		return (0);

	map->width = strlen(map->map[0]);
	i = 1;
	while (i < map->height)
	{
		if ((int)strlen(map->map[i]) != map->width)
			return (0);
		i++;
	}
	return (1);
}

int	is_exist(t_map *map)
{
	int		i;
	int		j;
	t_var	var;

	if (!map || !map->map)
		return (0);
	i = 0;
	var.player = 0;
	var.exit = 0;
	var.coins = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == 'P')
				var.player++;
			if (map->map[i][j] == 'E')
				var.exit++;
			if (map->map[i][j] == 'C')
				var.coins++;
			j++;
		}
		i++;
	}
	return (var.player == 1 && var.exit == 1 && var.coins > 0);
}

int	is_wall(t_map *map)
{
	int	i;
	int	j;

	if (!map || !map->map)
		return (0);
	i = 0;
	while (i < map->width)
	{
		if (map->map[0][i] != '1' || map->map[map->height - 1][i] != '1')
			return (0);
		i++;
	}
	j = 0;
	while (j < map->height)
	{
		if (map->map[j][0] != '1' || map->map[j][map->width - 1] != '1')
			return (0);
		j++;
	}
	return (1);
}


// void	flood_fill(t_map *map, int x, int y)
// {
// 	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
// 		return ;
// 	if (map->map[y][x] != '0')
// 		return ;
// 	map->map[y][x] = 'F';
// 	flood_fill(map, x + 1, y);
// 	flood_fill(map, x - 1, y);
// 	flood_fill(map, x, y + 1);
// 	flood_fill(map, x, y - 1);
// }

int	valid_map(t_map *map)
{
	if (!map || !map->map)
		return (0);
	
	if (!is_rectangular(map))
	{
		printf("lmap mam9adach\n");
		return (0);
	}
	if (!is_exist(map))
	{
		printf("na9sa chihaja f map\n");
		return (0);
	}
	if (!is_wall(map))
	{
		printf("lhit makamelch\n");
		return (0);
	}
	return (1);
}