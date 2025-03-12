/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 07:57:06 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/03/11 07:57:30 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map	*read_map(char *filename)
{
	char *line;
	int	fd;
	t_map	*map_data;
	int	i;
	int	lines;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	lines = count_lines(filename);
	map_data = malloc(sizeof(t_map));
	if (!map_data)
		return (NULL);
	map_data->map = malloc((lines + 1) * sizeof(char *));
	if (!map_data->map)
	{
		free(map_data);
		return (NULL);
	}
	map_data->height = lines;
	i = 0;
	line = get_next_line(fd);
	if (!line)
	{
		free(map_data->map);
		free(map_data);
		close(fd);
		return (NULL);
	}
	char *newline = strchr(line, '\n');
    if (newline)
        *newline = '\0';
    map_data->width = strlen(line); 
	while (line)
	{
		newline = strchr(line, '\n');
        if (newline)
            *newline = '\0';
		map_data->map[i] = strdup(line);
		if (!map_data->map[i])
		{
			while (i-- >= 0)
				free(map_data->map[i]);
			free(map_data->map);
			free(map_data);
			free(line);
			close(fd);
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	map_data->map[i] = NULL;
	close(fd);
	return (map_data);
}