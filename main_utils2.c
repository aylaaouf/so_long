/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 08:40:59 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/03/15 06:49:28 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(t_game *game)
{
	free_map(game->map);
	clean_game(game);
	exit(0);
	return (0);
}

int	no_collectible_more(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			if (game->map->map[i][j] == 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
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
