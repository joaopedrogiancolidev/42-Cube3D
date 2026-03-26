/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 17:30:32 by arthur            #+#    #+#             */
/*   Updated: 2026/03/26 18:23:00 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "parser.h"

static void	set_spawn_orientation(t_raycast *raycast, char spawn)
{
	if (spawn == 'N')
	{
		raycast->dir_x = 0.0;
		raycast->dir_y = -1.0;
		raycast->plane_x = 0.66;
		raycast->plane_y = 0.0;
	}
	else if (spawn == 'S')
	{
		raycast->dir_x = 0.0;
		raycast->dir_y = 1.0;
		raycast->plane_x = -0.66;
		raycast->plane_y = 0.0;
	}
	else if (spawn == 'E')
	{
		raycast->dir_x = 1.0;
		raycast->dir_y = 0.0;
		raycast->plane_x = 0.0;
		raycast->plane_y = 0.66;
	}
	else
	{
		raycast->dir_x = -1.0;
		raycast->dir_y = 0.0;
		raycast->plane_x = 0.0;
		raycast->plane_y = -0.66;
	}
}

static void	free_partial_map(int **map, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static int	copy_runtime_map(t_cube_data *cube_data, t_map_grid *map_grid)
{
	int		row;
	int		col;
	char	cell;

	cube_data->map = (int **)malloc(sizeof(int *) * map_grid->height);
	if (!cube_data->map)
		return (1);
	row = 0;
	while (row < map_grid->height)
	{
		cube_data->map[row] = (int *)malloc(sizeof(int) * map_grid->width);
		if (!cube_data->map[row])
			return (free_partial_map(cube_data->map, row), 1);
		col = 0;
		while (col < map_grid->width)
		{
			cell = map_grid->lines[row][col];
			cube_data->map[row][col] = (cell == '1' || cell == ' ') ? 1 : 0;
			if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
			{
				cube_data->raycast.pos_x = col + 0.5;
				cube_data->raycast.pos_y = row + 0.5;
				set_spawn_orientation(&cube_data->raycast, cell);
			}
			col++;
		}
		row++;
	}
	return (0);
}

int	parser(int argc, char **argv, t_cube_data *cube_data)
{
	t_parser_config	cfg;
	t_map_grid		map_grid;

	ft_memset(cube_data, 0, sizeof(*cube_data));
	if (argc != 2)
	{
		parser_error_usage();
		return (1);
	}
	if (parse_cub_file_data(argv[1], &cfg, &map_grid) != 0)
		return (1);
	cube_data->map_width = map_grid.width;
	cube_data->map_height = map_grid.height;
	cube_data->raycast.old_time = 0;
	if (copy_runtime_map(cube_data, &map_grid) != 0)
	{
		free_parser_config(&cfg);
		free_map_grid(&map_grid);
		printf("Error\nmemory allocation failed for runtime map\n");
		return (1);
	}
	free_parser_config(&cfg);
	free_map_grid(&map_grid);
	return (0);
}