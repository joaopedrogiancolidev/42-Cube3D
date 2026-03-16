NAME := game
# CFLAGS := -Wextra -Wall -Werror -Wunreachable-code -0fast
CFLAGS = 
LIBMLX := ./MLX42
OBJDIR := obj

HEADERS := -I ./include -I $(LIBMLX)/include
LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS := $(shell find ./src -iname "*.c")
OBJS := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

all: $(OBJDIR) libmlx $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJDIR)/%.o: src/%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx