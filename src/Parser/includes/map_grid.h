#ifndef MAP_GRID_H
# define MAP_GRID_H

/*
** Day 3: Map Grid Extraction and Normalization
** 
** This module handles the extraction and normalization of the map block from .cub files.
** Purpose:
**   - Accumulate raw map lines during parsing
**   - Extract to a rectangular grid (normalized width across all rows)
**   - Pad shorter lines with spaces to match max width for rectangular representation
** 
** Usage flow (from read_lines.c):
**   1. init_map_grid(&map) - initialize empty grid
**   2. add_map_line(&map, line, line_no) for each MAP line
**   3. extract_map_grid(&map) - normalize to rectangle, calculate width, print debug
**   4. free_map_grid(&map) - cleanup when done or on error
*/

typedef struct s_map_grid
{
	char	**lines;  /* Array of normalized map lines (width padded with spaces) */
	int		height;  /* Number of rows in the map */
	int		width;   /* Max width (used to pad all lines to same length) */
}t_map_grid;

void	init_map_grid(t_map_grid *map);
void	free_map_grid(t_map_grid *map);
int		add_map_line(t_map_grid *map, char *line, int line_no);
int		get_max_map_width(t_map_grid *map);
int		extract_map_grid(t_map_grid *map);

#endif