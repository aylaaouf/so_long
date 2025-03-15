/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 08:37:21 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/03/15 07:30:28 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->map)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->map[i])
				free(map->map[i]);
			i++;
		}
		free(map->map);
	}
	free(map);
}

void	free_images(t_game *game)
{
	if (!game || !game->mlx)
		return ;
	if (game->coin)
		mlx_destroy_image(game->mlx, game->coin);
	if (game->empty_space)
		mlx_destroy_image(game->mlx, game->empty_space);
	if (game->player)
		mlx_destroy_image(game->mlx, game->player);
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->gate)
		mlx_destroy_image(game->mlx, game->gate);
	game->coin = NULL;
	game->empty_space = NULL;
	game->player = NULL;
	game->wall = NULL;
	game->gate = NULL;
}

void	clean_game(t_game *game)
{
	if (!game)
		return ;
	free_images(game);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	free(game);
}

void	ft_putchar_s(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr_s(int nbr)
{
	if (nbr >= 10)
		ft_putnbr_s(nbr / 10);
	ft_putchar_s((nbr % 10) + '0');
}
