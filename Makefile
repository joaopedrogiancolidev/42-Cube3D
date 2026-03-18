NAME    := game
# CFLAGS  := -Wextra -Wall -Werror -Ofast
CFLAGS  := 

LIBMLX  := ./MLX42
OBJDIR  := obj

HEADERS := -I ./include -I $(LIBMLX)/include
LIBS    := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

# 1. Encontra todos os .c em qualquer subpasta de src
SRCS    := $(shell find src -type f -name "*.c")

# 2. Mapeia src/caminho/arquivo.c para obj/caminho/arquivo.o (Preservando a estrutura)
OBJS    := $(SRCS:src/%.c=$(OBJDIR)/%.o)

all: libmlx $(NAME)

libmlx:
	@if [ ! -d "$(LIBMLX)/build" ]; then \
		cmake $(LIBMLX) -B $(LIBMLX)/build; \
	fi
	@cmake --build $(LIBMLX)/build -j4

# 3. Regra mágica: Compila e cria a subpasta necessária dentro de obj/
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