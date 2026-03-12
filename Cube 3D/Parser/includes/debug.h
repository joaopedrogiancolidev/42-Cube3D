#ifndef DEBUG_H
# define DEBUG_H

# include "ft_printf.h"

# define DBG_COLOR_YELLOW "\033[33m"
# define DBG_COLOR_RESET "\033[0m"

# ifdef DEBUG_PARSER
#  define DBG_LINE(fn, line, result) \
	ft_printf(DBG_COLOR_YELLOW "[DEBUG] %s: [%s] -> %d" DBG_COLOR_RESET "\n", fn, line, result)
# else
#  define DBG_LINE(fn, line, result) ((void)0)
# endif

#endif
