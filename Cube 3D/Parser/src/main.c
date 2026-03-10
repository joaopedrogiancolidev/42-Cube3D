#include "parsing.h"
#include "utils.h"

#include <stdio.h>

int	main(int argc, char **argv)
{
	t_file_lines	file_lines;

	if (argc != 2)
	{
		printf("Usage: ./parser_demo <map.cub>\n");
		return (1);
	}
	if (!load_file_lines(argv[1], &file_lines))
	{
		printf("Error: could not read file: %s\n", argv[1]);
		return (1);
	}
	printf("Read %zu line(s) from %s\n\n", file_lines.count, argv[1]);
	print_file_lines(&file_lines);
	free_file_lines(&file_lines);
	return (0);
}