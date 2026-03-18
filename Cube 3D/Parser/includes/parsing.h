#ifndef PARSING_H
# define PARSING_H

int	is_empty_line(char *line);
int	is_element_line(char *line);
int	is_map_line(char *line);
int	classify_file_lines(int fd);
const char	*line_type_name(char *line);

#endif