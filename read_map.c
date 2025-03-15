/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 07:57:06 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/03/15 07:33:30 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_map	*allocate_map_data(char *filename)
{
	t_map	*map_data;

	map_data = malloc(sizeof(t_map));
	if (!map_data)
		return (NULL);
	map_data->height = count_lines(filename);
	map_data->map = malloc((map_data->height + 1) * sizeof(char *));
	if (!map_data->map)
	{
		free(map_data);
		return (NULL);
	}
	return (map_data);
}

static int	fill_map(int fd, t_map *map_data)
{
	char	*line;
	int		i;
	char	*newline;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		newline = ft_strchr_l(line, '\n');
		if (newline)
			*newline = '\0';
		if (i == 0)
			map_data->width = ft_strlen(line);
		map_data->map[i] = ft_strdup(line);
		free(line);
		if (!map_data->map[i])
			return (0);
		i++;
		line = get_next_line(fd);
	}
	map_data->map[i] = NULL;
	return (1);
}

t_map	*read_map(char *filename)
{
	int		fd;
	t_map	*map_data;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map_data = allocate_map_data(filename);
	if (!map_data)
		return (close(fd), NULL);
	if (!fill_map(fd, map_data))
	{
		free_map(map_data);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (map_data);
}
