/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:58:31 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/03/12 03:59:37 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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


void	flood_fill(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return ;
	if (map->map[y][x] != '0')
		return ;
	map->map[y][x] = 'F';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

void	valid_map(t_game *game, char *filename)
{
	game->map = read_map(filename);
	if (!game->map)
	{
		printf("Error: Failed to read map\n");
		free_map(game->map);
		clean_game(game);
		exit(1);
	}
	if (!is_rectangular(game->map))
	{
		printf("lmap mam9adach\n");
		free_map(game->map);
		clean_game(game);
		exit(1);
	}
	if (!is_exist(game->map))
	{
		printf("na9sa chihaja f map\n");
		free_map(game->map);
		clean_game(game);
		exit(1);
	}
	if (!is_wall(game->map))
	{
		printf("lhit makamelch\n");
		free_map(game->map);
		clean_game(game);
		exit(1);
	}
}