#include "parser.h"

void	parser_error_invalid_line(int line_no)
{
	ft_printf("Error: invalid line at %d\n", line_no);
}

void	parser_error_element_after_map(int line_no)
{
	ft_printf("Error: element after map started at line %d\n", line_no);
}

void	parser_error_duplicate(const char *key, int line_no)
{
	ft_printf("Error: duplicate element '%s' at line %d\n", key, line_no);
}

void	parser_error_missing(const char *key)
{
	ft_printf("Error: missing required element '%s'\n", key);
}

void	parser_error_malloc(const char *key, int line_no)
{
	ft_printf("Error: malloc failed while parsing '%s' at line %d\n", key,
		line_no);
}