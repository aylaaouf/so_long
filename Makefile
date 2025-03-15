NAME = so_long
SRC = main.c main_helper.c main_utils.c main_utils2.c parsing.c parsing_utils.c read_map.c flood_fill_algo.c gnl/get_next_line_utils.c gnl/get_next_line.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX = minilibx-linux
MLX_FLAGS = -L$(MLX) -lmlx -lXext -lX11
LIBFT = libft/libft.a
PRINTF = printf/libftprintf.a

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_FLAGS) -Llibft -lft -Lprintf -lftprintf

clean:
	rm -f $(OBJ)
	make clean -C libft
	make clean -C printf

fclean: clean
	rm -f $(NAME)
	make clean -C libft
	make clean -C printf

re: fclean all
