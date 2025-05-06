CC = cc
CFLAGS = -Wall -Wextra -Werror -g
# MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
MLX_FLAGS = -lmlx -lX11 -lXext -lbsd -lm
NAME = cub3D

SRC_DIR = .
PARSING_DIR = parsing
RAYTRACING_DIR = raytracing
OBJ_DIR = obj

MAIN_SRC = main.c

FT_PRINTF_DIR = parsing/ft_printf
GNL_DIR = parsing/get_next_line

PARSING_SRC = parsing/utils.c \
              parsing/utils2.c \
              parsing/utils3.c \
              parsing/parsing.c \
              parsing/main.c

RAYTRACING_SRC = raytracing/main.c \
                 raytracing/player.c

SRC = $(MAIN_SRC) $(PARSING_SRC) $(RAYTRACING_SRC)

OBJ = $(MAIN_SRC:%.c=$(OBJ_DIR)/%.o) \
      $(PARSING_SRC:%.c=$(OBJ_DIR)/%.o) \
      $(RAYTRACING_SRC:%.c=$(OBJ_DIR)/%.o)

INCLUDES = -I$(PARSING_DIR) -I$(RAYTRACING_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(FT_PRINTF_DIR)
	@make -C $(GNL_DIR)	
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(FT_PRINTF_DIR)/libftprintf.a $(GNL_DIR)/get_next_line.a -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make -C $(FT_PRINTF_DIR) clean
	@make -C $(GNL_DIR) clean	
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(FT_PRINTF_DIR) fclean
	@make -C $(GNL_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 