#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

typedef struct s_file_lines
{
	char	**lines;
	size_t	count;
}t_file_lines;

void	print_file_lines(const t_file_lines *file_lines);
void	free_file_lines(t_file_lines *file_lines);

#endif