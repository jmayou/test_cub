NAME = cub3d

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g


SRC = main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c utils.c utils2.c parsing.c utils3.c

OBJ = $(SRC:.c=.o)

FT_PRINTF_DIR = ft_printf

all: $(NAME)

$(NAME): $(OBJ) header.h
	@make -C $(FT_PRINTF_DIR)    
	$(CC) $(CFLAGS) $(OBJ) $(FT_PRINTF_DIR)/libftprintf.a -o $(NAME)

clean:
	@make -C $(FT_PRINTF_DIR) clean
	rm -rf $(OBJ)

fclean: clean
	@make -C $(FT_PRINTF_DIR) fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
