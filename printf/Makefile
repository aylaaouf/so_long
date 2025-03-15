CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_printf.c main.c
OBJS = $(SRCS:.c=.o)
NAME = libftprintf.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f *.a

re: fclean all

.PHONY: clean