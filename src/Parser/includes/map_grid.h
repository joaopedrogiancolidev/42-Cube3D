/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:35:03 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/03 15:36:00 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_GRID_H
# define MAP_GRID_H

/*
** Day 3: Map Grid Extraction and Normalization
** 
** This module handles the extraction and normalization of the
 map block from .cub files.
** Purpose:
**   - Accumulate raw map lines during parsing
**   - Extract to a rectangular grid 
(normalized width across all rows)
**   - Pad shorter lines with spaces to match max width 
for rectangular representation
** 
** Usage flow (from read_lines.c):
**   1. init_map_grid(&map) - initialize empty grid
**   2. add_map_line(&map, line, line_no) for each MAP line
**   3. extract_map_grid(&map) - 
normalize to rectangle, calculate width, print debug
**   4. free_map_grid(&map) - 
cleanup when done or on error
*/

/* Array of normalized map lines (width padded with spaces) */
/* Number of rows in the map */
/* Max width (used to pad all lines to same length) */

typedef struct s_map_grid
{
	char	**lines;
	int		height;
	int		width;
}t_map_grid;

void	init_map_grid(t_map_grid *map);
void	free_map_grid(t_map_grid *map);
int		add_map_line(t_map_grid *map, char *line, int line_no);
int		get_max_map_width(t_map_grid *map);
int		extract_map_grid(t_map_grid *map);

#endif