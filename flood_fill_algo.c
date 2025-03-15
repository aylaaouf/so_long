/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_algo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 06:41:32 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/03/15 07:06:08 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**copy_map(char **map, int len)
{
	char	**map_copy;
	int		i;

	map_copy = (char **)malloc((len + 1) * sizeof(char *));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		map_copy[i] = strdup(map[i]);
		if (!map_copy)
		{
			free_copy_of_map(map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

void	free_copy_of_map(char **map_copy)
{
	int	i;

	i = 0;
	if (!map_copy)
		return ;
	while (map_copy[i])
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

int	check_map_is_exist(char **map)
{
	int	i;
	int	j;

	if (!map)
		return (0);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C' || map[i][j] == 'E' || map[i][j] == 'P')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	flood_fill(char **map, int x, int y)
{
	if (x <= 0 || y <= 0 || map[y][x] == '1' || map[y][x] == 'X')
		return ;
	if (map[y][x] == 'E')
	{
		map[y][x] = '1';
		return ;
	}
	map[y][x] = 'X';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}
