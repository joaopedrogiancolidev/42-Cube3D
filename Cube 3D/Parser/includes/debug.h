#ifndef DEBUG_H
# define DEBUG_H

# include "ft_printf.h"

# define DBG_COLOR_YELLOW "\033[33m"
# define DBG_COLOR_CYAN "\033[36m"
# define DBG_COLOR_GREEN "\033[32m"
# define DBG_COLOR_RESET "\033[0m"

# ifdef DEBUG_PARSER
#  define DBG_LINE(fn, line, result) \
	ft_printf(DBG_COLOR_YELLOW "[DEBUG] %s -> %d" DBG_COLOR_RESET "\n", fn, result)
#  define DBG_CLASSIFIED_LINE(line_no, line_type, line) \
	do { \
		int	_dbg_len; \
		ft_printf(DBG_COLOR_CYAN "[LINE %d] %s | %s" DBG_COLOR_RESET, line_no, line_type, line); \
		_dbg_len = (int)ft_strlen(line); \
		if (_dbg_len == 0 || line[_dbg_len - 1] != '\n') \
			ft_printf("\n"); \
	} while (0)
#  define DBG_MAP_GRID_INFO(width, height) \
	ft_printf(DBG_COLOR_GREEN "[MAP GRID] width=%d height=%d" DBG_COLOR_RESET "\n", width, height)
#  define DBG_MAP_GRID_LINE(index, line) \
	ft_printf(DBG_COLOR_GREEN "[MAP %d] |%s|" DBG_COLOR_RESET "\n", index, line)
# else
#  define DBG_LINE(fn, line, result) ((void)0)
#  define DBG_CLASSIFIED_LINE(line_no, line_type, line) ((void)0)
#  define DBG_MAP_GRID_INFO(width, height) ((void)0)
#  define DBG_MAP_GRID_LINE(index, line) ((void)0)
# endif

#endif
