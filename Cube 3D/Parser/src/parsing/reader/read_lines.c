/*
** read_lines.c - Main parser orchestration (Dias 1-3)
** 
** load_file_lines(fd):
**   Orchestrates the entire parsing flow:
**   
**   Day 1-2: Parse configuration phase
**     - Line by line reading via get_next_line()
**     - Classify each line: EMPTY, ELEMENT, MAP, or INVALID
**     - Parse ELEMENT lines into config (NO/SO/WE/EA/F/C)
**     - Detect errors: duplicate element, element after map starts
**     - Validate all required elements are present
**   
**   Day 3: Map extraction and normalization phase
**     - Accumulate MAP lines in t_map_grid structure
**     - After config is valid, call extract_map_grid() to normalize
**     - Result: map stored as rectangular grid in memory
**   
**   Return: 0 if parsing succeeds, 1 if any error detected
*/

#include "parser.h"

int	load_file_lines(int fd)
{
	char	*line;
	char	*line_type;
	int		has_invalid;
	int		line_no;
	t_parser_config	cfg;
	t_map_grid	map;
	int		has_map_started;

	has_invalid = 0;
	line_no = 1;
	has_map_started = 0;
	init_parser_config(&cfg);
	init_map_grid(&map);
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
		{
			has_map_started = 1;
			if (add_map_line(&map, line, line_no) != 0)
				has_invalid = 1;
		}
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
	if (!has_invalid && extract_map_grid(&map) != 0)
	{
		has_invalid = 1;
		parser_error_malloc("MAP", line_no);
	}
	free_parser_config(&cfg);
	free_map_grid(&map);
	return (has_invalid);
}