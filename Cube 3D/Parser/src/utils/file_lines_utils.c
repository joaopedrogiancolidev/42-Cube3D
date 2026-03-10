#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

void	print_file_lines(const t_file_lines *file_lines)
{
	size_t	i;

	i = 0;
	while (i < file_lines->count)
	{
		printf("line[%zu] = [%s]\n", i, file_lines->lines[i]);
		i++;
	}
}

void	free_file_lines(t_file_lines *file_lines)
{
	size_t	i;

	if (!file_lines || !file_lines->lines)
		return ;
	i = 0;
	while (i < file_lines->count)
	{
		free(file_lines->lines[i]);
		i++;
	}
	free(file_lines->lines);
	file_lines->lines = NULL;
	file_lines->count = 0;
}