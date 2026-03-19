NAME    := game
# CFLAGS  := -Wextra -Wall -Werror -Ofast
CFLAGS  := 

LIBMLX  := ./MLX42
OBJDIR  := obj

HEADERS := -I ./include -I $(LIBMLX)/include
LIBS    := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS    := $(shell find src -type f -name "*.c")

OBJS    := $(SRCS:src/%.c=$(OBJDIR)/%.o)
all: libmlx $(NAME)
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

.PHONY: all clean fclean re libmlx