/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 03:54:40 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/03/15 08:06:28 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	mlx_images(t_game *game)
{
	int	width;
	int	height;

	game->coin = mlx_xpm_file_to_image(game->mlx, "./textures/coin.xpm", &width,
			&height);
	game->player = mlx_xpm_file_to_image(game->mlx, "./textures/player.xpm",
			&width, &height);
	game->wall = mlx_xpm_file_to_image(game->mlx, "./textures/wall.xpm", &width,
			&height);
	game->empty_space = mlx_xpm_file_to_image(game->mlx,
			"./textures/empty_space.xpm", &width, &height);
	game->gate = mlx_xpm_file_to_image(game->mlx, "./textures/gate.xpm", &width,
			&height);
	if (!game->coin || !game->player || !game->wall || !game->empty_space
		|| !game->gate)
	{
		printf("Error: Failed to load one or more images\n");
		free_images(game);
		clean_game(game);
		exit(1);
	}
}

void	draw_map_helper(t_game *game, char place, int x, int y)
{
	if (place == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->gate, x, y);
	else if (place == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game->coin, x, y);
	else if (place == 'P')
		mlx_put_image_to_window(game->mlx, game->win, game->player, x, y);
	else if (place == '0')
		mlx_put_image_to_window(game->mlx, game->win, game->empty_space, x, y);
	else if (place == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->wall, x, y);
}

void	draw_map(t_game *game)
{
	int	i;
	int	j;

	mlx_clear_window(game->mlx, game->win);
	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			draw_map_helper(game, game->map->map[i][j],
				j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
}

void	move_player(int new_x, int new_y, t_game *game)
{
	if (new_x < 0 || new_x >= game->map->width || new_y < 0
		|| new_y >= game->map->height)
		return ;
	if (game->map->map[new_y][new_x] == 'E' && no_collectible_more(game))
	{
		write(1, "You Won!\n", 9);
		close_window(game);
	}
	if (game->map->map[new_y][new_x] != '1'
		&& game->map->map[new_y][new_x] != 'E')
	{
		game->map->map[game->player_y][game->player_x] = '0';
		game->player_x = new_x;
		game->player_y = new_y;
		game->map->map[game->player_y][game->player_x] = 'P';
	}
}

void	handle_movement(int key, t_pos *pos, int *count, t_game *game)
{
	if (key == UP_KEY && game->map->map[pos->y - 1][pos->x] != '1')
		pos->y--;
	else if (key == DOWN_KEY && game->map->map[pos->y + 1][pos->x] != '1')
		pos->y++;
	else if (key == LEFT_KEY && game->map->map[pos->y][pos->x - 1] != '1')
		pos->x--;
	else if (key == RIGHT_KEY && game->map->map[pos->y][pos->x + 1] != '1')
		pos->x++;
	else
		return ;
	(*count)++;
	ft_putnbr(*count);
	write(1, "\n", 1);
}
