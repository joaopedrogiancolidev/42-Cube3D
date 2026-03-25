#ifndef ELEMENTS_H
# define ELEMENTS_H

# include "parser_config.h"

int	parse_element_line(t_parser_config *cfg, char *line, int line_no);
int	validate_required_elements(t_parser_config *cfg, const char *source_path);

#endif