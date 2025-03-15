/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:37:52 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/03/15 06:30:11 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_press(int key, t_game *game)
{
	int			new_x;
	int			new_y;
	static int	count;

	new_x = game->player_x;
	new_y = game->player_y;
	if (key == ESC_KEY)
	{
		printf("Exiting the game...\n");
		close_window(game);
	}
	else
		handle_movement(key, &new_x, &new_y, &count);
	move_player(new_x, new_y, game);
	draw_map(game);
	return (0);
}

t_game	*init_game(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
	{
		printf("Usage: ./so_long map.ber\n");
		return (NULL);
	}
	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	memset(game, 0, sizeof(t_game));
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		free(game);
		return (NULL);
	}
	valid_map(game, av[1]);
	return (game);
}

void	find_player_position(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			if (game->map->map[i][j] == 'P')
			{
				game->player_y = i;
				game->player_x = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	setup_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx, game->map->width * TILE_SIZE,
			game->map->height * TILE_SIZE, "so_long");
	mlx_images(game);
	draw_map(game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = init_game(ac, av);
	if (!game || !game->map)
	{
		printf("Error: Invalid map or failed to read map\n");
		clean_game(game);
		return (0);
	}
	find_player_position(game);
	setup_window(game);
	return (1);
}
