#include "parser.h"

/*
** Visual marker used only by parser_demo to make terminal output easier to scan.
*/
static void	print_visual_separator(void)
{
	ft_printf("\n----PARSER ERROR MANAGER:----\n\n");
}

/*
** Entry point for parser_demo.
** Why it exists:
** - Validate CLI usage and open the .cub file.
** - Delegate all parsing work to load_file_lines().
** - Convert parser result to process exit code (0 success, 1 error).
*/
int	main(int argc, char **argv)
{
	int		fd;
	int		has_invalid;

       print_visual_separator();
	if (argc != 2)
	{
		ft_printf("Usage: ./parser_demo <map.cub>\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: could not open file: %s\n", argv[1]);
		return (1);
	}
	has_invalid = load_file_lines(fd);
	close(fd);
	if (has_invalid)
		return (1);
	return (0);
}