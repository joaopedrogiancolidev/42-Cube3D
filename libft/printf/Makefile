# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/14 23:59:17 by jgiancol          #+#    #+#              #
#    Updated: 2025/08/20 10:15:11 by jgiancol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

INC_DIR = includes

LIB_SRCS = \
    ft_printf.c \
    parse/specifier_chars.c \
    parse/specifiers_filters.c \
    parse/specifier_nbrs.c \
    utils/utils.c

OBJS_DIR = obj

DIRS = $(OBJS_DIR) $(addprefix $(OBJS_DIR)/, parse utils)

LIB_OBJS = $(patsubst %.c, $(OBJS_DIR)/%.o, $(LIB_SRCS))

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(DIRS) $(NAME)

$(NAME): $(LIB_OBJS)
	ar rcs $(NAME) $(LIB_OBJS)

$(OBJS_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(DIRS):
	mkdir -p $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re $(DIRS)