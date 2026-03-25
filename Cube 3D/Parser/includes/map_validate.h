#ifndef MAP_VALIDATE_H
# define MAP_VALIDATE_H

# include "map_grid.h"

/*
** Used by load_file_lines() after extract_map_grid() to validate
** the normalized map before later gameplay-specific checks.
*/
int	validate_map_charset_and_spawn(t_map_grid *map);

/*
** Day 5: map closure validation on the normalized rectangular grid.
** Used after charset/spawn validation to ensure no walkable cell leaks to void.
*/
int	validate_map_closed(t_map_grid *map);

#endif