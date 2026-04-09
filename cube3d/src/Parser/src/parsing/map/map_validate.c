/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 23:23:22 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/08 00:33:23 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_spawn_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_walkable_char(char c)
{
	return (c == '0' || is_spawn_char(c));
}

static int	is_open_cell(t_map_grid *map, int row, int col)
{
	if (row == 0 || col == 0 || row == map->height - 1 || col == map->width - 1)
		return (1);
	if (map->lines[row - 1][col] == ' ' || map->lines[row + 1][col] == ' '
		|| map->lines[row][col - 1] == ' ' || map->lines[row][col + 1] == ' ')
		return (1);
	return (0);
}

int	validate_map_closed(t_map_grid *map)
{
	int	row;
	int	col;

	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			if (is_walkable_char(map->lines[row][col])
				&& is_open_cell(map, row, col))
			{
				parser_error_map_open(row + 1, col + 1, map->lines[row][col]);
				return (1);
			}
			col++;
		}
		row++;
	}
	return (0);
}
