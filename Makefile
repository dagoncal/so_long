NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = so_long.c
OBJS = ${SRCS:.c=.o}

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
