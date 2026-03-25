#ifndef MAP_VALIDATE_H
# define MAP_VALIDATE_H

# include "map_grid.h"

/*
** Used by load_file_lines() after extract_map_grid() to validate
** the normalized map before later gameplay-specific checks.
*/
int	validate_map_charset_and_spawn(t_map_grid *map);

#endif