NAME    := game
# CFLAGS  := -Wextra -Wall -Werror -Ofast
CFLAGS  := 

LIBMLX  := ./MLX42
LIBFT_DIR := ./libft
PRINTF_DIR := $(LIBFT_DIR)/printf
LIBFT := $(LIBFT_DIR)/libft.a
LIBPRINTF := $(PRINTF_DIR)/libftprintf.a
OBJDIR  := obj

HEADERS := -I ./include -I $(LIBMLX)/include -I ./src/Parser/includes -I $(LIBFT_DIR) -I $(PRINTF_DIR)/includes
LIBS    := $(LIBMLX)/build/libmlx42.a $(LIBFT) $(LIBPRINTF) -ldl -lglfw -pthread -lm

SRCS_CORE := $(shell find src -type f -name "*.c" ! -path "src/Parser/*")
SRCS_PARSER := $(shell find src/Parser/src/parsing -type f -name "*.c")
SRCS    := $(SRCS_CORE) $(SRCS_PARSER)

OBJS    := $(SRCS:src/%.c=$(OBJDIR)/%.o)
all: libs libmlx $(NAME)

libs:
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(PRINTF_DIR)

libmlx:
	@if [ ! -d "$(LIBMLX)/build" ]; then \
		cmake $(LIBMLX) -B $(LIBMLX)/build; \
	fi
	@cmake --build $(LIBMLX)/build -j4

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo "\n✅ $(NAME) compilado com sucesso!"

clean:
	@rm -rf $(OBJDIR)
	@echo "🧹 Objetos removidos."

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBMLX)/build
	@echo "🧼 Limpeza completa."

re: fclean all

.PHONY: all libs clean fclean re libmlx