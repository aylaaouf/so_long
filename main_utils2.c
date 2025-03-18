/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 08:40:59 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/03/18 21:21:56 by aylaaouf         ###   ########.fr       */
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
	int		i;
	int		j;
	char	**map2;

	map2 = map->map;
	if (!map || !map->map || !map->map[0])
		return (0);
	i = 0;
	while (map2[i])
	{
		j = i + 1;
		while (map2[j])
		{
			if (ft_strlen(map2[i]) != ft_strlen(map2[j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
