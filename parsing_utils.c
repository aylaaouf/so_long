/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:56:28 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/03/15 07:27:45 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
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
