#include "parser.h"

/*
** Entry point for parser_demo.
** Why it exists:
** - Validate CLI usage and open the .cub file.
** - Delegate all parsing work to load_file_lines().
** - Convert parser result to process exit code (0 success, 1 error).
*/
int	main(int argc, char **argv)
{
	int		has_invalid;

	if (argc != 2)
	{
		parser_error_usage();
		return (1);
	}
	has_invalid = parse_cub_file(argv[1]);
	if (has_invalid)
		return (1);
	return (0);
}