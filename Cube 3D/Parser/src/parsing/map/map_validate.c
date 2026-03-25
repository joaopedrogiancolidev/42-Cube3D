/*
** map_validate.c - Day 4: Structural map validation
**
** Validations:
**   1) Allowed charset in normalized grid: '0', '1', 'N', 'S', 'E', 'W', ' '
**   2) Exactly one spawn marker among 'N', 'S', 'E', 'W'
*/

#include "parser.h"

/*
** Exists to keep spawn rules centralized in one helper.
** Used by is_allowed_map_char() and validate_map_charset_and_spawn().
*/
static int	is_spawn_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/*
** Exists to define the Day 4 allowed charset in one place.
** Used by validate_map_charset_and_spawn() while iterating the grid.
*/
static int	is_allowed_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || is_spawn_char(c));
}

/*
** Main Day 4 validation entry point.
** Called from load_file_lines() after map normalization because validation
** must run against the final rectangular representation (map->width/height).
**
** Why it exists:
** - Prevent invalid symbols from entering later map logic.
** - Enforce exactly one player spawn before Day 5 closure checks.
*/
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
			if (!is_allowed_map_char(map->lines[row][col]))
			{
				DBG_MAP_VALIDATE_CHAR(row + 1, col + 1, map->lines[row][col]);
				parser_error_map_invalid_char(row + 1, col + 1,
					map->lines[row][col]);
				return (1);
			}
			if (is_spawn_char(map->lines[row][col]))
				spawn_count++;
			col++;
		}
		row++;
	}
	DBG_MAP_VALIDATE_SPAWN(spawn_count);
	if (spawn_count != 1)
	{
		parser_error_spawn_count(spawn_count);
		return (1);
	}
	return (0);
}