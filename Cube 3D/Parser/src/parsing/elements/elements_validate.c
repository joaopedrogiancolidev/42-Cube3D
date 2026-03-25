#include "parser.h"

/*
** Emits missing-element error for one key if its value is NULL.
** Used by validate_required_elements() to keep checks compact.
*/
static int	print_missing_if_null(char *value, const char *key)
{
	if (!value)
	{
		parser_error_missing(key);
		return (1);
	}
	return (0);
}

/*
** Day 2 post-parse validation for required config keys.
** Called by load_file_lines() after the file has been read.
*/
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