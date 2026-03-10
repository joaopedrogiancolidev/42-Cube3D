#include "parsing.h"
#include "utils.h"
#include "visual.h"

#include <stdio.h>

static void	print_legend(void)
{
	printf("Legend:\n");
	printf("  1 -> wall (dark blue)\n");
	printf("  0 -> floor (light gray)\n");
	printf("  N -> spawn north (red)\n");
	printf("  S -> spawn south (blue)\n");
	printf("  E -> spawn east (green)\n");
	printf("  W -> spawn west (purple)\n");
	printf("  open/suspicious -> yellow\n");
	printf("  space/void -> black\n\n");
}

int	main(int argc, char **argv)
{
	t_file_lines	file_lines;
	t_map_grid	map_grid;

	if (argc != 2)
	{
		printf("Usage: ./visual_demo <map.cub>\n");
		return (1);
	}
	if (!load_file_lines(argv[1], &file_lines))
		return (printf("Error: could not read file\n"), 1);
	if (!extract_map_grid(&file_lines, &map_grid))
		return (free_file_lines(&file_lines),
			printf("Error: could not extract map grid\n"), 1);
	printf("Visualizing map (%zux%zu).\n", map_grid.width, map_grid.height);
	print_legend();
	if (!run_visual_demo(&map_grid))
		printf("Error: could not open MLX window\n");
	free_map_grid(&map_grid);
	free_file_lines(&file_lines);
	return (0);
}