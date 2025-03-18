/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:56:28 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/03/18 21:19:51 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_size_width_height(char **map, int *height, int *width)
{
	*height = 0;
	*width = 0;
	while (map[*height])
		(*height)++;
	while (map[0][*width])
		(*width)++;
}

int	count_lines(char *filename)
{
	int		count;
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: Wrong path");
		return (-1);
	}
	line = get_next_line(fd);
	count = 0;
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

int	is_exist(t_map *map)
{
	t_var	var;

	int i, (j);
	if (!map || !map->map)
		return (0);
	i = 0;
	var.player = 0;
	var.exit = 0;
	var.coins = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'P')
				var.player++;
			if (map->map[i][j] == 'E')
				var.exit++;
			if (map->map[i][j] == 'C')
				var.coins++;
			j++;
		}
		i++;
	}
	return (var.player == 1 && var.exit == 1 && var.coins > 0);
}

int	find_enemy_before(t_game *game)
{
	int y, (x);
	y = 0;
	x = 0;
	while (game->map->map[y])
	{
		x = 0;
		while (game->map->map[y][x])
		{
			if (game->map->map[y][x] == 'X')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}
