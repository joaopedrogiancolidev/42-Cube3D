/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_charset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 00:10:00 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/07 23:59:02 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_spawn_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_allowed_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || is_spawn_char(c));
}

static int	validate_cell_charset_and_spawn(t_map_grid *map, int row,
		int col, int *spawn_count)
{
	char	c;

	c = map->lines[row][col];
	if (!is_allowed_map_char(c))
	{
		parser_error_map_invalid_char(row + 1, col + 1, c);
		return (1);
	}
	if (is_spawn_char(c))
		(*spawn_count)++;
	return (0);
}

int	validate_map_charset_and_spawn(t_map_grid *map)
{
	int	row;
	int	col;
	int	spawn_count;

	row = 0;
	spawn_count = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			if (validate_cell_charset_and_spawn(map, row, col, &spawn_count))
				return (1);
			col++;
		}
		row++;
	}
	if (spawn_count != 1)
	{
		parser_error_spawn_count(spawn_count);
		return (1);
	}
	return (0);
}
