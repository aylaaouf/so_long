/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:58:31 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/03/20 01:53:02 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_wall(t_map *map)
{
	int	i;
	int	j;

	if (!map || !map->map)
		return (0);
	get_size_width_height(map->map, &map->height, &map->width);
	i = 0;
	while (i < map->width)
	{
		if (map->map[0][i] != '1' || map->map[map->height - 1][i] != '1')
			return (0);
		i++;
	}
	j = 0;
	while (j < map->height)
	{
		if (map->map[j][0] != '1' || map->map[j][map->width - 1] != '1')
			return (0);
		j++;
	}
	return (1);
}

int	check_path(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len <= 4 || ft_strncmp(filename + len - 4, ".ber", 4) != 0
		|| filename[len - 5] == '/')
		return (0);
	return (1);
}

void	valid_map_helper(t_game *game, char *filename)
{
	get_size_width_height(game->map->map, &game->map->height,
		&game->map->width);
	if (!game->map)
	{
		ft_printf("Error: Failed to read map.\n");
		free_map(game->map);
		clean_game(game);
		exit(0);
	}
	if (!check_path(filename))
	{
		ft_printf("Error: Invalid path.\n");
		free_map(game->map);
		clean_game(game);
		exit(0);
	}
	if (!is_rectangular(game->map))
	{
		ft_printf("Error: Map is not rectangular.\n");
		free_map(game->map);
		clean_game(game);
		exit(0);
	}
}

int	is_valid_path(t_map *map, int player_x, int player_y)
{
	char	**map_copy;
	int		flag;

	map_copy = copy_map(map->map, map->height);
	if (!map_copy)
		return (0);
	flood_fill(map_copy, player_x, player_y);
	flag = check_map_is_exist(map_copy);
	free_copy_of_map(map_copy);
	return (flag);
}

void	valid_map(t_game *game, char *filename)
{
	game->map = read_map(filename);
	valid_map_helper(game, filename);
	get_size_width_height(game->map->map,
		&game->map->height, &game->map->width);
	if (!is_exist(game->map))
	{
		ft_printf("Error: Map is not complete.\n");
		free_map(game->map);
		clean_game(game);
		exit(0);
	}
	if (!is_wall(game->map))
	{
		ft_printf("Error: Wall is not complete.\n");
		free_map(game->map);
		clean_game(game);
		exit(0);
	}
	find_player_position(game);
	if (!is_valid_path(game->map, game->player_x, game->player_y))
		helper_valid_path(game);
}
