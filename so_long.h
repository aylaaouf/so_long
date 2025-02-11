#ifndef SO_LONG_H
#define SO_LONG_H

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "gnl/get_next_line.h"

#define TILE_SIZE 64

typedef struct s_map
{
	int	width;
	int	height;
	char **map;
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	int		player_x;
	int		player_y;
	t_map	*map;
}	t_game;

typedef struct s_var
{
	int	player;
	int	exit;
	int	coins;
}	t_var;

enum keys
{
	ESC_KEY = 65307,
	UP_KEY = 65362,
	DOWN_KEY = 65364,
	LEFT_KEY = 65361,
	RIGHT_KEY = 65363
};

int		is_rectangular(t_map *map);
int		is_exist(t_map *map);
int		is_wall(t_map *map);
t_map	*read_map(char *filename);
int		valid_map(t_map *map);

#endif
