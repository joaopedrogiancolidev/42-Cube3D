/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 00:20:00 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/08 00:32:01 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	print_error_prefix(void)
{
	ft_printf("Error\n");
}

void	parser_error_malloc(const char *key, int line_no)
{
	print_error_prefix();
	ft_printf("malloc failed while parsing '%s' at line %d\n", key,
		line_no);
}

void	parser_error_map_invalid_char(int row, int col, char c)
{
	print_error_prefix();
	ft_printf("invalid map character '%c' at row %d col %d\n",
		c, row, col);
}

void	parser_error_spawn_count(int spawn_count)
{
	print_error_prefix();
	ft_printf("expected exactly 1 spawn, found %d\n", spawn_count);
}

void	parser_error_map_open(int row, int col, char c)
{
	print_error_prefix();
	ft_printf("map is open at row %d col %d around '%c'\n",
		row, col, c);
}
