#include "minilibx-linux/mlx.h"
#include "so_long.h"

void	draw_map(t_game *game)
{
	int	i;
	int	j;
	int	width;
	int	height;

	i = 0;
	void *coin = mlx_xpm_file_to_image(game->mlx, "./textures/coin.xpm", &width, &height);
	void *player = mlx_xpm_file_to_image(game->mlx, "./textures/player.xpm", &width, &height);
	void *wall = mlx_xpm_file_to_image(game->mlx, "./textures/wall.xpm", &width, &height);
	void *empty_space = mlx_xpm_file_to_image(game->mlx, "./textures/empty_space.xpm", &width, &height);
	mlx_clear_window(game->mlx, game->win);
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			if (game->map->map[i][j] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, coin, j * TILE_SIZE, i * TILE_SIZE);
			if (game->map->map[i][j] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, player, j * TILE_SIZE, i * TILE_SIZE);
			if (game->map->map[i][j] == '0')
				mlx_put_image_to_window(game->mlx, game->win, empty_space, j * TILE_SIZE, i * TILE_SIZE);
			if (game->map->map[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->win, wall, j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
}

int		no_collectible_more(t_game *game)
{
	int	i;
	int j;

	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			if (game->map->map[i][j] == 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nbr)
{
	if (nbr >= 10)
		ft_putnbr(nbr / 10);
	ft_putchar((nbr % 10) + '0');
}

void	move_player(int new_x, int new_y, t_game *game)
{
	static int	count;

	if (new_x < 0 || new_x >= game->map->width || new_y < 0 || new_y >= game->map->height)
		return ;
	if (game->map->map[new_y][new_x] == 'E' && no_collectible_more(game))
	{
		mlx_destroy_window(game->mlx, game->win);
		write(1, "You Won!\n", 9);
		exit(0);
	}
	if (game->map->map[new_y][new_x] == 'X')
	{
		mlx_destroy_window(game->mlx, game->win);
		write(1, "Game Over!\n", 11);
		exit(0);
	}
	if (game->map->map[new_y][new_x] != '1' && game->map->map[new_y][new_x] != 'E')
	{
		game->map->map[game->player_y][game->player_x] = '0';
		game->player_x = new_x;
		game->player_y = new_y;
		game->map->map[game->player_y][game->player_x] = 'P';
		count++;
		ft_putnbr(count);
		write(1, "\n", 1);
	}
}

int	key_press(int key, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x;
	new_y = game->player_y;
	if (key == ESC_KEY)
	{
		printf("derti esc khrej t9wd\n");
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	else if (key == UP_KEY)
		new_y -= 1;
	else if (key == DOWN_KEY)
		new_y += 1;
	else if (key == LEFT_KEY)
		new_x -= 1;
	else if (key == RIGHT_KEY)
		new_x += 1;
	move_player(new_x, new_y,  game);
	draw_map(game);
	return (0);
}

int main(int ac, char **av)
{
	t_game	*game;
	int	i;
	int	j;

	game = malloc(sizeof(t_game));
	if (ac != 2)
	{
		printf("Usage: ./so_long map.ber\n");
		return (0);
	}
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->map = read_map(av[1]);
	if (!game->map || !valid_map(game->map))
	{
		if (game->map)
			free(game->map);
		free(game);
		return (0);
	}
	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			if (game->map->map[i][j] == 'P')
			{
				game->player_y = i;
				game->player_x = j;
			}
			j++;
		}
		i++;
	}
	game->win = mlx_new_window(game->mlx, game->map->width * TILE_SIZE, game->map->height * TILE_SIZE, "so_long");
	draw_map(game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_loop(game->mlx);
	return (1);
}
