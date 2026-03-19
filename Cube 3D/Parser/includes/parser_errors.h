#ifndef PARSER_ERRORS_H
# define PARSER_ERRORS_H

void	parser_error_invalid_line(int line_no);
void	parser_error_element_after_map(int line_no);
void	parser_error_duplicate(const char *key, int line_no);
void	parser_error_missing(const char *key);
void	parser_error_malloc(const char *key, int line_no);

#endif