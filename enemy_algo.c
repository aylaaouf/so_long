/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 10:44:26 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/03/15 15:44:18 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_enemy(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map->map[y])
	{
		x = 0;
		while (game->map->map[y][x])
		{
			if (game->map->map[y][x] == 'X')
			{
				game->enemy.x = x;
				game->enemy.y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	helper(t_game *game)
{
	ft_printf("Game Over! enemy caught you.\n");
	free_map(game->map);
	clean_game(game);
	exit(0);
}

void	move_func(t_enemy *enemy, int new_x, int new_y)
{
	new_x = enemy->x;
	new_y = enemy->y;
	enemy->direction = rand() % 4;
	if (enemy->direction == 0)
		new_x--;
	else if (enemy->direction == 1)
		new_x++;
	else if (enemy->direction == 2)
		new_y--;
	else if (enemy->direction == 3)
		new_y++;
}

void	move_enemy(t_game *game, t_enemy *enemy)
{
	int	new_x;
	int	new_y;
	int	tries;

	tries = 0;
	while (tries < 4)
	{
		move_func(enemy, new_x, new_y);
		if (game->map->map[new_y][new_x] != '1'
			&& game->map->map[new_y][new_x] != 'E'
			&& game->map->map[new_y][new_x] != 'C')
		{
			if (game->map->map[new_y][new_x] == 'P')
				helper(game);
			game->map->map[enemy->y][enemy->x] = '0';
			enemy->x = new_x;
			enemy->y = new_y;
			game->map->map[enemy->y][enemy->x] = 'X';
			return ;
		}
		tries++;
	}
}

int	enemy_patrol(t_game *game)
{
	static int	counter;

	if (counter++ < 10000)
		return (0);
	counter = 0;
	move_enemy(game, &game->enemy);
	return (0);
}
