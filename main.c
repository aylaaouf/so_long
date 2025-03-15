/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:37:52 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/03/15 10:31:28 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_press(int key, t_game *game)
{
	t_pos		pos;
	static int	count;

	pos.x = game->player_x;
	pos.y = game->player_y;
	if (key == ESC_KEY)
	{
		ft_printf("Exiting the game...\n");
		close_window(game);
	}
	else
		handle_movement(key, &pos, &count, game);
	move_player(pos.x, pos.y, game);
	draw_map(game);
	return (0);
}

t_game	*init_game(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
	{
		ft_printf("Usage: ./so_long map.ber\n");
		return (NULL);
	}
	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	ft_memset(game, 0, sizeof(t_game));
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
	mlx_key_hook(game->win, key_press, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = init_game(ac, av);
	if (!game || !game->map)
	{
		ft_printf("Error: Invalid map or failed to read map\n");
		clean_game(game);
		return (0);
	}
	find_player_position(game);
	setup_window(game);
	return (1);
}
