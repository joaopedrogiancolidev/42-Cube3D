#include "parser.h"

/* Generic line-level parse error used by early classification flow. */
void	parser_error_invalid_line(int line_no)
{
	ft_printf("Error: invalid line at %d\n", line_no);
}

/* Emitted when an element appears after map parsing has started. */
void	parser_error_element_after_map(int line_no)
{
	ft_printf("Error: element after map started at line %d\n", line_no);
}

/* Emitted by Day 2 element parser when a key is defined more than once. */
void	parser_error_duplicate(const char *key, int line_no)
{
	ft_printf("Error: duplicate element '%s' at line %d\n", key, line_no);
}

/* Emitted by Day 2 required-element validation for missing config fields. */
void	parser_error_missing(const char *key)
{
	ft_printf("Error: missing required element '%s'\n", key);
}

/* Shared allocator error used by element/map modules. */
void	parser_error_malloc(const char *key, int line_no)
{
	ft_printf("Error: malloc failed while parsing '%s' at line %d\n", key,
		line_no);
}

/* Used by Day 4 validators when a map symbol is outside allowed charset. */
void	parser_error_map_invalid_char(int row, int col, char c)
{
	ft_printf("Error: invalid map character '%c' at row %d col %d\n",
		c, row, col);
}

/* Used by Day 4 spawn validation to enforce exactly one player start. */
void	parser_error_spawn_count(int spawn_count)
{
	ft_printf("Error: expected exactly 1 spawn, found %d\n", spawn_count);
}