#ifndef VISUAL_H
# define VISUAL_H

# include "utils.h"

typedef struct s_map_grid
{
	char	**rows;
	size_t	height;
	size_t	width;
}t_map_grid;

int		extract_map_grid(const t_file_lines *file_lines, t_map_grid *map_grid);
void	free_map_grid(t_map_grid *map_grid);
int		run_visual_demo(const t_map_grid *map_grid);

#endif