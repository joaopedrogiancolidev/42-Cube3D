/*
** map_extract.c - Day 3: Map normalization and rectangular grid extraction
** 
** Functions:
**   get_max_map_width() - Find longest line in the accumulated map block
**   extract_map_grid() - Transform ragged lines into rectangular grid:
**                       1. Calculate width (longest line)
**                       2. Allocate normalized array
**                       3. For each line: create new string of exactly 'width' length,
**                          copy original content, pad remaining with spaces
**                       4. Replace old ragged array with normalized array
**                       5. Print debug info if DEBUG_PARSER is set
** 
** Result: map->lines now contains 'height' strings, each exactly 'width' chars,
**         representing the map layout as it was in the file but in a rectangular form.
*/

#include "parser.h"

/*
** Computes target width for normalization by finding the longest map row.
** Used by extract_map_grid() before allocating the rectangular buffer.
*/
int	get_max_map_width(t_map_grid *map)
{
	int	i;
	int	max_width;
	int	line_len;

	i = 0;
	max_width = 0;
	while (i < map->height)
	{
		line_len = (int)ft_strlen(map->lines[i]);
		if (line_len > max_width)
			max_width = line_len;
		i++;
	}
	return (max_width);
}

/*
** Creates one normalized row of fixed width and pads with spaces.
** Used by extract_map_grid() for each original map line.
*/
static int	normalize_line(char **dst, char *src, int width)
{
	int	line_len;

	*dst = (char *)malloc(sizeof(char) * (width + 1));
	if (!*dst)
		return (1);
	ft_memset(*dst, ' ', width);
	line_len = (int)ft_strlen(src);
	if (line_len > 0)
		ft_memcpy(*dst, src, line_len);
	(*dst)[width] = '\0';
	return (0);
}

/*
** Cleanup helper for partial allocation failures during normalization.
** Used only by extract_map_grid() error path.
*/
static void	free_partial_normalized(char **lines, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

/*
** Debug-only map dump after normalization.
** Used by extract_map_grid() to make Day 3 output easy to verify visually.
*/
static void	debug_print_map_grid(t_map_grid *map)
{
	int	i;
	i = 0;
	while (i < map->height)
	{
		i++;
	}
}

/*
** Day 3 normalization entry point.
** Called by load_file_lines() after map accumulation is complete.
** Why it exists: convert ragged input rows into a rectangular grid used by
** later validations (Day 4+).
*/
int	extract_map_grid(t_map_grid *map)
{
	char	**normalized;
	int		i;

	map->width = get_max_map_width(map);
	if (map->height == 0 || map->width == 0)
		return (0);
	normalized = (char **)malloc(sizeof(char *) * map->height);
	if (!normalized)
		return (1);
	i = 0;
	while (i < map->height)
	{
		if (normalize_line(&normalized[i], map->lines[i], map->width))
		{
			free_partial_normalized(normalized, i);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		free(map->lines[i]);
		i++;
	}
	free(map->lines);
	map->lines = normalized;
	debug_print_map_grid(map);
	return (0);
}