NAME		= cube3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -Iincludes -I../libft -I../libft/printf/includes

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= $(SRC_DIR)/main.c

OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR	= ../libft
LIBFT		= $(LIBFT_DIR)/libft.a

PRINTF_DIR	= ../libft/printf
LIBPRINTF	= $(PRINTF_DIR)/libftprintf.a

MLX_DIR		= ../MLX42
MLX_BUILD_DIR	= $(MLX_DIR)/build

all: libs mlx $(NAME)

libs:
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(PRINTF_DIR)

mlx:
	cmake -S $(MLX_DIR) -B $(MLX_BUILD_DIR)
	cmake --build $(MLX_BUILD_DIR) -j

mlx_clean:
	rm -rf $(MLX_BUILD_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBPRINTF) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(PRINTF_DIR) fclean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += -DDEBUG
debug: re

.PHONY: all libs mlx mlx_clean clean fclean re debug
