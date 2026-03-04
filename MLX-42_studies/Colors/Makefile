NAME := test_mlx_colors
CFLAGS := -Wextra -Wall -Werror -Wunreachable-code -O2
LIBMLX := ../../MLX42

HEADERS := -I ./include -I $(LIBMLX)/include
LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS := $(shell find ./src -iname "*.c")
OBJS := $(SRCS:./src/%.c=./obj/%.o)
OBJDIR := ./obj

all: $(OBJDIR) libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: ./src/%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) && printf "\n✓ Executável criado: $(NAME)\n"

run: all
	@./$(NAME)

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, libmlx, run
