/*
** parse_cub_file.c - Day 6: consolidated parser entry pipeline
**
** parse_cub_file(path):
**   1) Open .cub file
**   2) Run load_file_lines(fd)
**   3) Close file and return parser status
**
** Why it exists:
** - Keep the parser flow centralized outside CLI/demo concerns.
** - Reuse one stable entry point for future integration in Cube3D runtime.
*/

#include "parser.h"

/* Enforces mandatory .cub input extension before parsing starts. */
static int	has_cub_extension(const char *path)
{
	int	len;

	len = (int)ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + (len - 4), ".cub", 4) == 0);
}

int	parse_cub_file(const char *path)
{
	int	fd;
	int	has_invalid;

	if (!has_cub_extension(path))
	{
		parser_error_invalid_extension(path);
		return (1);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		parser_error_file_open(path);
		return (1);
	}
	has_invalid = load_file_lines(fd, path);
	close(fd);
	return (has_invalid);
}
