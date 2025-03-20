/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 03:21:32 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/03/20 05:57:36 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
// # include <mlx.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include "printf/ft_printf.h"

# define TILE_SIZE 64

typedef struct s_map
{
	int		width;
	int		height;
	char	**map;
}			t_map;

typedef struct s_enemy
{
	int		x;
	int		y;
	int		direction;
}			t_enemy;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	int		player_x;
	int		player_y;
	int		moves_count;
	char	*moves_count_str;
	t_map	*map;
	void	*player;
	void	*empty_space;
	void	*killer;
	void	*wall;
	void	*coin;
	void	*gate;
	void	*animation;
	t_enemy	enemy;
	int		enemy_count;
}			t_game;

typedef struct s_var
{
	int		player;
	int		exit;
	int		coins;
}			t_var;

enum		e_keys
{
	ESC_KEY = 65307,
	UP_KEY = 65362,
	DOWN_KEY = 65364,
	LEFT_KEY = 65361,
	RIGHT_KEY = 65363
};

typedef struct s_pos
{
	int		x;
	int		y;
}			t_pos;

// helpers for main file "norminette"
int			check_path(char *filename);
void		helper_valid_path(t_game *game);
void		get_size_width_height(char **map, int *height, int *width);
void		mlx_images(t_game *game);
void		draw_map_helper(t_game *game, char place, int x, int y);
void		draw_map(t_game *game);
void		move_player(int new_x, int new_y, t_game *game);
void		handle_movement(int key, t_pos *pos, t_game *game);

// parsing
void		invalid_char(t_game *game);
void		find_player_position(t_game *game);
void		free_copy_of_map(char **map_copy);
void		flood_fill(char **map, int x, int y);
int			check_map_is_exist(char **map);
char		**copy_map(char **map, int len);
int			is_rectangular(t_map *map);
int			is_wall(t_map *map);
int			count_lines(char *filename);
t_map		*read_map(char *filename);
int			is_exist(t_map *map);
int			no_collectible_more(t_game *game);
void		valid_map(t_game *game, char *filename);

// utils
void		ft_putchar_s(char c);
void		ft_putnbr_s(int nbr);

// free func
void		free_map(t_map *map);
void		clean_game(t_game *game);
void		free_images(t_game *game);
int			close_window(t_game *game);

// game
int			no_collectible_more(t_game *game);

// enemy
void		find_enemy(t_game *game);
int			find_enemy_before(t_game *game);
int			enemy_patrol(t_game *game);
void		helper(t_game *game);

#endif
