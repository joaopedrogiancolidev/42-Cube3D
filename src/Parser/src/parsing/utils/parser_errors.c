/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 14:22:31 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/04 14:22:35 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Common subject-compliant error prefix. */
static void	print_error_prefix(void)
{
	ft_printf("Error\n");
}

/* Generic line-level parse error used by early classification flow. */
void	parser_error_invalid_line(int line_no)
{
	print_error_prefix();
	ft_printf("invalid line at line %d\n", line_no);
}

/* Emitted when an element appears after map parsing has started. */
void	parser_error_element_after_map(int line_no)
{
	print_error_prefix();
	ft_printf("element after map started at line %d\n", line_no);
}

/* Emitted by Day 2 element parser when a key is defined more than once. */
void	parser_error_duplicate(const char *key, int line_no)
{
	print_error_prefix();
	ft_printf("duplicate element '%s' at line %d\n", key, line_no);
}

/* Emitted by Day 2 required-element validation for missing config fields. */
void	parser_error_missing(const char *key)
{
	print_error_prefix();
	ft_printf("missing required element '%s'\n", key);
}

/* Shared allocator error used by element/map modules. */
void	parser_error_malloc(const char *key, int line_no)
{
	print_error_prefix();
	ft_printf("malloc failed while parsing '%s' at line %d\n", key,
		line_no);
}

/* Used by Day 4 validators when a map symbol is outside allowed charset. */
void	parser_error_map_invalid_char(int row, int col, char c)
{
	print_error_prefix();
	ft_printf("invalid map character '%c' at row %d col %d\n",
		c, row, col);
}

/* Used by Day 4 spawn validation to enforce exactly one player start. */
void	parser_error_spawn_count(int spawn_count)
{
	print_error_prefix();
	ft_printf("expected exactly 1 spawn, found %d\n", spawn_count);
}

/* Used by Day 5 closure validation when walkable cells leak into void/boundary. */
void	parser_error_map_open(int row, int col, char c)
{
	print_error_prefix();
	ft_printf("map is open at row %d col %d around '%c'\n",
		row, col, c);
}

/* Used when F/C values do not match mandatory RGB constraints. */
void	parser_error_invalid_rgb(const char *key)
{
	print_error_prefix();
	ft_printf("invalid RGB value for '%s' (expected R,G,B in [0,255])\n", key);
}

/* Used when a mandatory texture path is missing or unreadable. */
void	parser_error_invalid_texture(const char *key, const char *path)
{
	print_error_prefix();
	ft_printf("invalid texture path for '%s': %s\n", key, path);
}

/* Emitted by parser_demo when CLI arguments are invalid. */
void	parser_error_usage(void)
{
	print_error_prefix();
	ft_printf("usage: ./parser_demo <map.cub>\n");
}

/* Emitted when parse_cub_file() cannot open the provided path. */
void	parser_error_file_open(const char *path)
{
	print_error_prefix();
	ft_printf("could not open file: %s\n", path);
}

/* Emitted when input path does not use the .cub extension. */
void	parser_error_invalid_extension(const char *path)
{
	print_error_prefix();
	ft_printf("invalid file extension (expected .cub): %s\n", path);
}