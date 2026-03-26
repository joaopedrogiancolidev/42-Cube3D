/*
** map_grid_utils.c - Day 3: Map grid initialization, accumulation, and cleanup
** 
** Functions:
**   init_map_grid() - Reset grid to empty state (NULL lines, 0 height/width)
**   free_map_grid() - Free all allocated lines and reset to empty
**   add_map_line() - Append a new (cleaned) line to the growing array
** 
** Note: Lines are stored WITHOUT trailing \n (stripped by dup_line_without_newline)
** This allows extract_map_grid() to normalize them cleanly to a rectangle.
*/

#include "parser.h"

/*
** Initializes map accumulator used while reading MAP lines.
** Called once by load_file_lines() before any map content is processed.
*/
void	init_map_grid(t_map_grid *map)
{
	map->lines = NULL;
	map->height = 0;
	map->width = 0;
}

/*
** Frees accumulated/normalized map memory and resets fields.
** Called on all parser exits to guarantee cleanup.
*/
void	free_map_grid(t_map_grid *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(map->lines[i]);
		i++;
	}
	free(map->lines);
	map->lines = NULL;
	map->height = 0;
	map->width = 0;
}

/*
** Duplicates one map line while stripping trailing '\n'.
** Used by add_map_line() so map storage is independent from file newlines.
*/
static char	*dup_line_without_newline(char *line)
{
	int		len;
	char	*copy;

	len = (int)ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	if (len > 0)
		ft_memcpy(copy, line, len);
	copy[len] = '\0';
	return (copy);
}

/*
** Appends one map line to the dynamic map->lines array.
** Called by load_file_lines() for each MAP-classified line.
*/
int	add_map_line(t_map_grid *map, char *line, int line_no)
{
	char	**new_lines;
	char	*clean_line;
	int		i;

	clean_line = dup_line_without_newline(line);
	if (!clean_line)
	{
		parser_error_malloc("MAP", line_no);
		return (1);
	}
	new_lines = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!new_lines)
	{
		free(clean_line);
		parser_error_malloc("MAP", line_no);
		return (1);
	}
	i = 0;
	while (i < map->height)
	{
		new_lines[i] = map->lines[i];
		i++;
	}
	new_lines[map->height] = clean_line;
	free(map->lines);
	map->lines = new_lines;
	map->height++;
	return (0);
}