#ifndef DEBUG_H
# define DEBUG_H

# include "ft_printf.h"

# define DBG_COLOR_YELLOW "\033[33m"
# define DBG_COLOR_CYAN "\033[36m"
# define DBG_COLOR_RESET "\033[0m"

# ifdef DEBUG_PARSER
#  define DBG_LINE(fn, line, result) \
	ft_printf(DBG_COLOR_YELLOW "[DEBUG] %s -> %d" DBG_COLOR_RESET "\n", fn, result)
#  define DBG_CLASSIFIED_LINE(line_no, line_type, line) \
	ft_printf(DBG_COLOR_CYAN "[LINE %d] %s | %s" DBG_COLOR_RESET, line_no, line_type, line)
# else
#  define DBG_LINE(fn, line, result) ((void)0)
#  define DBG_CLASSIFIED_LINE(line_no, line_type, line) ((void)0)
# endif

#endif
