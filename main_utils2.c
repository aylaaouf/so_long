/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 08:40:59 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/03/11 08:41:25 by aylaaouf         ###   ########.fr       */
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

int		no_collectible_more(t_game *game)
{
	int	i;
	int j;

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