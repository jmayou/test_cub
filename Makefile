NAME = cub3D

CC = gcc

CFLAGS =# -Wall -Wextra -Werror 

# linux
# MLX_FLAGS = -lmlx -lX11 -lXext -lbsd -lm
# mac
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit


SRC = main.c player.c

OBJ = $(SRC:.c=.o)

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_FLAGS)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all
