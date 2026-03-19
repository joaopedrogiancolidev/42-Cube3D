NAME = parser_demo
CC = cc
BASE_CFLAGS = -Wall -Wextra -Werror
CFLAGS = $(BASE_CFLAGS)
INCLUDES = -Iincludes -I../../libft
SRC_DIR = src
OBJ_DIR = obj
SRCS = $(SRC_DIR)/main_parser.c \
	$(SRC_DIR)/parsing/types/line_types.c \
	$(SRC_DIR)/parsing/reader/read_lines.c \
	$(SRC_DIR)/parsing/config/parser_config.c \
	$(SRC_DIR)/parsing/elements/elements_parse.c \
	$(SRC_DIR)/parsing/elements/elements_validate.c \
	$(SRC_DIR)/parsing/map/map_grid_utils.c \
	$(SRC_DIR)/parsing/map/map_extract.c \
	$(SRC_DIR)/parsing/utils/parser_errors.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT_DIR = ../../libft
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF_DIR = ../../libft/printf
LIBPRINTF = $(PRINTF_DIR)/libftprintf.a
MLX_DIR = ../../MLX42
MLX_BUILD_DIR = $(MLX_DIR)/build

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
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(LIBPRINTF) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += -DDEBUG_PARSER
debug: re

.PHONY: all libs mlx mlx_clean clean fclean re debug
