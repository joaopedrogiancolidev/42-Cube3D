NAME = parser_demo
VISUAL_NAME = visual_demo
CC = cc
BASE_CFLAGS = -Wall -Wextra -Werror
CFLAGS = $(BASE_CFLAGS)
INCLUDES = -Iincludes
SRC_DIR = src
OBJ_DIR = obj
SRCS = $(SRC_DIR)/main.c \
	$(SRC_DIR)/parsing/load_file.c \
	$(SRC_DIR)/utils/file_lines_utils.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
VISUAL_SRCS = $(SRC_DIR)/visual_main.c \
	$(SRC_DIR)/parsing/load_file.c \
	$(SRC_DIR)/utils/file_lines_utils.c \
	$(SRC_DIR)/visual/extract_map.c \
	$(SRC_DIR)/visual/render_map.c
VISUAL_OBJS = $(VISUAL_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
MLX_DIR = ../../MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a
GLFW_LIB = $(MLX_DIR)/build/_deps/glfw-build/src/libglfw3.a
MLX_INCLUDES = -I$(MLX_DIR)/include
MLX_FLAGS = $(MLX_LIB) $(GLFW_LIB) -ldl -pthread -lm -lX11 -lXrandr -lXi -lXxf86vm -lXinerama -lXcursor -lXext

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(MLX_INCLUDES) $(OBJS) -o $(NAME)

visual: $(VISUAL_NAME)

$(VISUAL_NAME): $(VISUAL_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(MLX_INCLUDES) $(VISUAL_OBJS) $(MLX_FLAGS) -o $(VISUAL_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) $(MLX_INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(VISUAL_OBJS)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(VISUAL_NAME)

re: fclean all

debug: CFLAGS += -DDEBUG_PARSER
debug: re

.PHONY: all clean fclean re debug visual
