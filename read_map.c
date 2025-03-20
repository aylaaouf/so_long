/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 07:57:06 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/03/20 01:38:55 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map_2(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

static void	clean_line(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static char	**fill_map(char ***map, int fd)
{
	char	*line;
	int		size;

	size = 0;
	line = get_next_line(fd);
	while (line)
	{
		clean_line(line);
		if (line[0] == '\0')
		{
			free(line);
			break ;
		}
		*map = realloc(*map, (size + 1) * sizeof(char *));
		if (!(*map))
			return (free(*map), free_map_2(*map), NULL);
		(*map)[size++] = line;
		line = get_next_line(fd);
	}
	*map = realloc(*map, (size + 1) * sizeof(char *));
	if (!(*map))
		return (free_map_2(*map), NULL);
	(*map)[size] = NULL;
	return (*map);
}

t_map	*read_map(char *filename)
{
	int		fd;
	t_map	*map_data;
	char	**map;

	map = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map_data = malloc(sizeof(t_map));
	ft_memset(map_data, 0, sizeof(t_map));
	if (!map_data)
		return (close(fd), NULL);
	map_data->map = fill_map(&map, fd);
	get_next_line(-1);
	close(fd);
	if (!map_data->map)
	{
		free(map_data);
		return (NULL);
	}
	return (map_data);
}
