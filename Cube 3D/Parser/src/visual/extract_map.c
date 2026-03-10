#include "visual.h"

#include <stdlib.h>
#include <string.h>

static int	is_map_char(char ch)
{
	return (ch == ' ' || ch == '0' || ch == '1'
		|| ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W');
}

static int	is_map_line(const char *line)
{
	size_t	i;
	int		has_map_content;

	i = 0;
	has_map_content = 0;
	while (line[i])
	{
		if (!is_map_char(line[i]))
			return (0);
		if (line[i] == '0' || line[i] == '1'
			|| line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			has_map_content = 1;
		i++;
	}
	return (has_map_content);
}

static size_t	find_map_start(const t_file_lines *file_lines)
{
	size_t	i;

	i = 0;
	while (i < file_lines->count)
	{
		if (is_map_line(file_lines->lines[i]))
			return (i);
		i++;
	}
	return (file_lines->count);
}

static size_t	find_map_end(const t_file_lines *file_lines, size_t start)
{
	size_t	i;

	i = start;
	while (i < file_lines->count)
	{
		if (!is_map_line(file_lines->lines[i]))
			break ;
		i++;
	}
	return (i);
}

static int	alloc_map_rows(t_map_grid *map_grid)
{
	size_t	y;

	map_grid->rows = malloc(sizeof(char *) * map_grid->height);
	if (!map_grid->rows)
		return (0);
	y = 0;
	while (y < map_grid->height)
	{
		map_grid->rows[y] = NULL;
		y++;
	}
	return (1);
}

int	extract_map_grid(const t_file_lines *file_lines, t_map_grid *map_grid)
{
	size_t	start;
	size_t	end;
	size_t	y;
	size_t	line_len;

	start = find_map_start(file_lines);
	if (start == file_lines->count)
		return (0);
	end = find_map_end(file_lines, start);
	map_grid->height = end - start;
	map_grid->width = 0;
	map_grid->rows = NULL;
	y = start;
	while (y < end)
	{
		line_len = strlen(file_lines->lines[y]);
		if (line_len > map_grid->width)
			map_grid->width = line_len;
		y++;
	}
	if (!alloc_map_rows(map_grid))
		return (0);
	y = 0;
	while (y < map_grid->height)
	{
		map_grid->rows[y] = malloc(map_grid->width + 1);
		if (!map_grid->rows[y])
			return (0);
		memset(map_grid->rows[y], ' ', map_grid->width);
		line_len = strlen(file_lines->lines[start + y]);
		memcpy(map_grid->rows[y], file_lines->lines[start + y], line_len);
		map_grid->rows[y][map_grid->width] = '\0';
		y++;
	}
	return (1);
}

void	free_map_grid(t_map_grid *map_grid)
{
	size_t	y;

	if (!map_grid || !map_grid->rows)
		return ;
	y = 0;
	while (y < map_grid->height)
	{
		free(map_grid->rows[y]);
		y++;
	}
	free(map_grid->rows);
	map_grid->rows = NULL;
	map_grid->height = 0;
	map_grid->width = 0;
}