#include "parser.h"

static int	print_missing_if_null(char *value, const char *key)
{
	if (!value)
	{
		parser_error_missing(key);
		return (1);
	}
	return (0);
}

int	validate_required_elements(t_parser_config *cfg)
{
	int	has_error;

	has_error = 0;
	has_error |= print_missing_if_null(cfg->no_path, "NO");
	has_error |= print_missing_if_null(cfg->so_path, "SO");
	has_error |= print_missing_if_null(cfg->we_path, "WE");
	has_error |= print_missing_if_null(cfg->ea_path, "EA");
	has_error |= print_missing_if_null(cfg->f_raw, "F");
	has_error |= print_missing_if_null(cfg->c_raw, "C");
	return (has_error);
}