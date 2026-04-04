#include "parser.h"

/*
** Day 1 line classification module.
**
** Why this file exists:
** - Keep lexical line typing isolated from semantic parsing logic.
** - Provide a simple classifier used by load_file_lines() to dispatch flow.
*/

/*
** Returns 1 when a line has only spaces/tabs and optional line ending.
** Used by line_type_name() as the first classifier check.
*/

int	is_empty_line(char *line)
{
	int	i;
	int	result;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	result = (line[i] == '\0' || line[i] == '\n');
	return (result);
}

/*
** Returns 1 when a line starts with one of the 6 element keys.
** Used by line_type_name() to route the line to element parsing.
*/
int	is_element_line(char *line)
{
	char	*raw_line;
	int	result;

	raw_line = line;
	(void)raw_line;
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		result = 1;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		result = 1;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		result = 1;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		result = 1;
	else if (ft_strncmp(line, "F ", 2) == 0)
		result = 1;
	else if (ft_strncmp(line, "C ", 2) == 0)
		result = 1;
	else
		result = 0;
	return (result);
}

/*
** Returns 1 when the line contains only map charset characters and
** at least one map token. Used by line_type_name() before INVALID.
*/

int	is_map_line(char *line)
{
	int	i;
	int	has_map_char;
	int	result;

    i = 0;
    has_map_char = 0;
    while (line[i] != '\0' && line[i] != '\n')
    {
        if (line[i] == ' ')
        {
            i++;
			continue;
        }
        if (line[i] == '0' || line[i] == '1' || line[i] == 'N'
            || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
        {
            has_map_char = 1;
            i++;
			continue;
        }
        result = 0;
        return (result);
    }
    result = has_map_char;
    return (result);
}

char	*line_type_name(char *line)
{
    /*
    ** Central classifier used by load_file_lines() to dispatch each line
    ** into parsing flow: EMPTY, ELEMENT, MAP, or INVALID.
    */
	if (is_empty_line(line))
		return ("EMPTY");
	if (is_element_line(line))
		return ("ELEMENT");
	if (is_map_line(line))
		return ("MAP");
	return ("INVALID");
}