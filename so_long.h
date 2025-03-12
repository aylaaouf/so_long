#ifndef SO_LONG_H
#define SO_LONG_H

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "gnl/get_next_line.h"
#include "minilibx-linux/mlx.h"

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
	void	*player;
	void	*empty_space;
	void	*wall;
	void	*coin;
	void	*gate;
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


//parsing
int		is_rectangular(t_map *map);
int		is_wall(t_map *map);
int		count_lines(char *filename);
t_map	*read_map(char *filename);
int		is_exist(t_map *map);
int		no_collectible_more(t_game *game);
void		valid_map(t_game *game, char *filename);

//utils
void	ft_putchar(char c);
void	ft_putnbr(int nbr);


//free
void	free_map(t_map *map);
void	clean_game(t_game *game);
void	free_images(t_game *game);
int		close_window(t_game *game);

//game
int		no_collectible_more(t_game *game);
#endif
