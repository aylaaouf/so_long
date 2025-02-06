#ifndef SO_LONG_H
#define SO_LONG_H

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "gnl/get_next_line.h"

typedef struct s_game
{
	void	*mlx;
	void	*win;
	int		player_x;
	int		player_y;
}	t_game;

typedef struct s_map
{
	int	width;
	int	height;
	char **map;
}	t_map;

typedef struct s_var
{
	int	player;
	int	exit;
	int	coins;
}	t_var;

enum keys
{
	ESC_KEY = 65307
	
};

t_map	*read_map(char *filename);

#endif
