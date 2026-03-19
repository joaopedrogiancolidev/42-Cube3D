#include "parser.h"

int	load_file_lines(int fd)
{
	char	*line;
	char	*line_type;
	int		has_invalid;
	int		line_no;
	t_parser_config	cfg;
	int		has_map_started;

	has_invalid = 0;
	line_no = 1;
	has_map_started = 0;
	init_parser_config(&cfg);
	line = get_next_line(fd);
	while (line)
	{
		line_type = (char *)line_type_name(line);
		if (ft_strncmp(line_type, "ELEMENT", 8) == 0)
		{
			if (has_map_started)
			{
				has_invalid = 1;
				parser_error_element_after_map(line_no);
			}
			else if (parse_element_line(&cfg, line, line_no) != 0)
				has_invalid = 1;
		}
		if (ft_strncmp(line_type, "MAP", 4) == 0)
			has_map_started = 1;
		if (ft_strncmp(line_type, "INVALID", 8) == 0)
		{
			has_invalid = 1;
			parser_error_invalid_line(line_no);
		}
		DBG_CLASSIFIED_LINE(line_no, line_type, line);
		free(line);
		line = get_next_line(fd);
		line_no++;
	}
	if (!has_invalid)
		has_invalid = validate_required_elements(&cfg);
	free_parser_config(&cfg);
	return (has_invalid);
}