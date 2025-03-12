/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:37:52 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/03/12 05:08:58 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	mlx_images(t_game *game)
{
	int	width;
	int	height;
	
	game->coin = mlx_xpm_file_to_image(game->mlx, "./textures/coin.xpm", &width, &height);
	game->player = mlx_xpm_file_to_image(game->mlx, "./textures/player.xpm", &width, &height);
	game->wall = mlx_xpm_file_to_image(game->mlx, "./textures/wall.xpm", &width, &height);
	game->empty_space = mlx_xpm_file_to_image(game->mlx, "./textures/empty_space.xpm", &width, &height);
	game->gate = mlx_xpm_file_to_image(game->mlx, "./textures/gate.xpm", &width, &height);

	if (!game->coin || !game->player || !game->wall || !game->empty_space || !game->gate)
	{
		printf("Error: Failed to load one or more images\n");
		free_images(game);
		clean_game(game);
		exit(1);
	}
}
void	draw_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	mlx_clear_window(game->mlx, game->win);
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			if (game->map->map[i][j] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->gate, j * TILE_SIZE, i * TILE_SIZE);
			if (game->map->map[i][j] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->coin, j * TILE_SIZE, i * TILE_SIZE);
			if (game->map->map[i][j] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->player, j * TILE_SIZE, i * TILE_SIZE);
			if (game->map->map[i][j] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->empty_space, j * TILE_SIZE, i * TILE_SIZE);
			if (game->map->map[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall, j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
}

void	move_player(int new_x, int new_y, t_game *game)
{
	if (new_x < 0 || new_x >= game->map->width || new_y < 0 || new_y >= game->map->height)
		return ;
	if (game->map->map[new_y][new_x] == 'E' && no_collectible_more(game))
	{
		write(1, "You Won!\n", 9);
		close_window(game);
	}
	if (game->map->map[new_y][new_x] != '1' && game->map->map[new_y][new_x] != 'E')
	{
		game->map->map[game->player_y][game->player_x] = '0';
		game->player_x = new_x;
		game->player_y = new_y;
		game->map->map[game->player_y][game->player_x] = 'P';
	}
}

int	key_press(int key, t_game *game)
{
	int	new_x;
	int	new_y;
	static int	count;

	new_x = game->player_x;
	new_y = game->player_y;
	if (key == ESC_KEY)
	{
		printf("Exiting the game...\n");
		close_window(game);
	}
	else if (key == UP_KEY)
	{
		count++;
		new_y -= 1;
		ft_putnbr(count);
		write(1, "\n", 1);
	}
	else if (key == DOWN_KEY)
	{
		count++;
		new_y += 1;
		ft_putnbr(count);
		write(1, "\n", 1);
	}
	else if (key == LEFT_KEY)
	{
		count++;
		new_x -= 1;
		ft_putnbr(count);
		write(1, "\n", 1);
	}
	else if (key == RIGHT_KEY)
	{
		count++;
		new_x += 1;
		ft_putnbr(count);
		write(1, "\n", 1);
	}
	move_player(new_x, new_y,  game);
	draw_map(game);
	return (0);
}

int main(int ac, char **av)
{
	t_game	*game;
	int	i;
	int	j;

	game = malloc(sizeof(t_game));
	memset(game, 0, sizeof(t_game));
	if (!game)
		return (0);
	if (ac != 2)
	{
		printf("Usage: ./so_long map.ber\n");
		return (0);
	}
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	valid_map(game, av[1]);
	if (!game->map)
	{
		// printf("Error: Invalid map or failed to read map\n");
		if (game->map)
			free_map(game->map);
		if (game->mlx)
			clean_game(game);
		else
			free(game);
		return (0);
	}
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
			}
			j++;
		}
		i++;
	}
	game->win = mlx_new_window(game->mlx, game->map->width * TILE_SIZE, game->map->height * TILE_SIZE, "so_long");
	mlx_images(game);
	draw_map(game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	// mlx_hook(game->win, 17, 0, close_window, game);	
	mlx_loop(game->mlx);
	// clean_game(game);
	return (1);
}
