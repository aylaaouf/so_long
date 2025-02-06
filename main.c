#include "minilibx-linux/mlx.h"
#include "so_long.h"

int	key_press(int key)
{
	if (key == ESC_KEY)
	{
		printf("derti esc khrej t9wd\n");
		exit(0);
	}
	return (0);
}

int main()
{
	t_game	game;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 500, 500, "so_long");

	mlx_key_hook(game.win, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
