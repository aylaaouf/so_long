NAME = so_long
SRC = main.c main_helper.c main_utils.c main_utils2.c parsing.c parsing_utils.c read_map.c flood_fill_algo.c gnl/get_next_line_utils.c gnl/get_next_line.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX = minilibx-linux
MLX_FLAGS = -L$(MLX) -lmlx -lXext -lX11

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_FLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
