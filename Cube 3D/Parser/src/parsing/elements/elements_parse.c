#include "parser.h"

/*
** Utility shared by parsing helpers to skip leading indentation.
** Used before key/value extraction in element lines.
*/
static char	*skip_spaces(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

/*
** Stores one parsed element value and protects against duplicates.
** Called by parse_element_line() once the key has been identified.
*/
static int	set_element_value(char **dst, char *value, const char *key,
		int line_no)
{
	if (*dst)
	{
		parser_error_duplicate(key, line_no);
		return (1);
	}
	*dst = ft_strdup(value);
	if (!*dst)
	{
		parser_error_malloc(key, line_no);
		return (1);
	}
	return (0);
}

/*
** Day 2 element parser.
** Used by load_file_lines() when line_type is ELEMENT.
** Why it exists: isolate element-key decoding from line reader flow.
*/
int	parse_element_line(t_parser_config *cfg, char *line, int line_no)
{
	char	*start;
	char	*value;

	start = skip_spaces(line);
	if (ft_strncmp(start, "NO ", 3) == 0)
	{
		value = skip_spaces(start + 3);
		return (set_element_value(&cfg->no_path, value, "NO", line_no));
	}
	else if (ft_strncmp(start, "SO ", 3) == 0)
	{
		value = skip_spaces(start + 3);
		return (set_element_value(&cfg->so_path, value, "SO", line_no));
	}
	else if (ft_strncmp(start, "WE ", 3) == 0)
	{
		value = skip_spaces(start + 3);
		return (set_element_value(&cfg->we_path, value, "WE", line_no));
	}
	else if (ft_strncmp(start, "EA ", 3) == 0)
	{
		value = skip_spaces(start + 3);
		return (set_element_value(&cfg->ea_path, value, "EA", line_no));
	}
	else if (ft_strncmp(start, "F ", 2) == 0)
	{
		value = skip_spaces(start + 2);
		return (set_element_value(&cfg->f_raw, value, "F", line_no));
	}
	else if (ft_strncmp(start, "C ", 2) == 0)
	{
		value = skip_spaces(start + 2);
		return (set_element_value(&cfg->c_raw, value, "C", line_no));
	}
	return (1);
}