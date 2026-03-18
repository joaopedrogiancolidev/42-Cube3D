#include "parser.h"

int	classify_file_lines(int fd)
{
	char	*line;
	char	*line_type;
	int		has_invalid;
	int		line_no;

	has_invalid = 0;
	line_no = 1;
	line = get_next_line(fd);
	while (line)
	{
		line_type = (char *)line_type_name(line);
		if (ft_strncmp(line_type, "INVALID", 8) == 0)
		{
			has_invalid = 1;
			ft_printf("Error: invalid line at %d\n", line_no);
		}
		DBG_CLASSIFIED_LINE(line_no, line_type, line);
		free(line);
		line = get_next_line(fd);
		line_no++;
	}
	return (has_invalid);
}