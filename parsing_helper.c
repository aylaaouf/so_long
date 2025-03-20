/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 07:12:23 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/03/20 07:20:14 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	helper_parsing(t_game *game, char *filename)
{
	if (!check_path(filename))
	{
		ft_printf("Error: Invalid path.\n");
		clean_game(game);
		exit(0);
	}
	game->map = read_map(filename);
	if (game->map == NULL)
	{
		perror("so_long");
		clean_game(game);
		exit(1);
	}
}
