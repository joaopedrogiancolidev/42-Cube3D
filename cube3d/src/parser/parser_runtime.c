/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_runtime.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:00:00 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/08 00:17:00 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "parser.h"

static void	set_raycast_dir_plane(t_raycast *raycast, double dx,
		double dy, double px)
{
	raycast->dir_x = dx;
	raycast->dir_y = dy;
	raycast->plane_x = px;
	if (px == 0.0)
	{
		if (dx == 1.0)
			raycast->plane_y = 0.66;
		else
			raycast->plane_y = -0.66;
	}
	else
		raycast->plane_y = 0.0;
}

static void	set_spawn_orientation(t_raycast *raycast, char spawn)
{
	if (spawn == 'N')
		set_raycast_dir_plane(raycast, 0.0, -1.0, 0.66);
	else if (spawn == 'S')
		set_raycast_dir_plane(raycast, 0.0, 1.0, -0.66);
	else if (spawn == 'E')
		set_raycast_dir_plane(raycast, 1.0, 0.0, 0.0);
	else
		set_raycast_dir_plane(raycast, -1.0, 0.0, 0.0);
}

static void	fill_map_row(t_cube_data *cube_data, t_map_grid *map_grid,
		int row)
{
	int		col;
	char	cell;

	col = 0;
	while (col < map_grid->width)
	{
		cell = map_grid->lines[row][col];
		if (cell == '1' || cell == ' ')
			cube_data->map[row][col] = 1;
		else
			cube_data->map[row][col] = 0;
		if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
		{
			cube_data->raycast.pos_x = col + 0.5;
			cube_data->raycast.pos_y = row + 0.5;
			set_spawn_orientation(&cube_data->raycast, cell);
		}
		col++;
	}
}

int	copy_runtime_map(t_cube_data *cube_data, t_map_grid *map_grid)
{
	int	row;

	cube_data->map = (int **)malloc(sizeof(int *) * map_grid->height);
	if (!cube_data->map)
		return (1);
	row = 0;
	while (row < map_grid->height)
	{
		cube_data->map[row] = (int *)malloc(sizeof(int) * map_grid->width);
		if (!cube_data->map[row])
		{
			while (row > 0)
			{
				row--;
				free(cube_data->map[row]);
			}
			free(cube_data->map);
			return (1);
		}
		fill_map_row(cube_data, map_grid, row);
		row++;
	}
	return (0);
}

void	transfer_config_to_cube(t_cube_data *cube_data, t_parser_config *cfg,
								t_map_grid *map_grid)
{
	int			i;

	cube_data->no_path = cfg->no_path;
	cfg->no_path = NULL;
	cube_data->so_path = cfg->so_path;
	cfg->so_path = NULL;
	cube_data->we_path = cfg->we_path;
	cfg->we_path = NULL;
	cube_data->ea_path = cfg->ea_path;
	cfg->ea_path = NULL;
	i = 0;
	while (i < 3)
	{
		cube_data->floor_rgb[i] = cfg->floor_rgb[i];
		cube_data->ceiling_rgb[i] = cfg->ceiling_rgb[i];
		i++;
	}
	cube_data->map_width = map_grid->width;
	cube_data->map_height = map_grid->height;
	cube_data->raycast.old_time = 0;
}
