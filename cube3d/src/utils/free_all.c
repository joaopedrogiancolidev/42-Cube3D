/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:48:42 by arthur            #+#    #+#             */
/*   Updated: 2026/04/08 15:18:59 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	free_textures(t_cube_data *cube_data)
{
	if (cube_data->tex_no)
	{
		mlx_delete_texture(cube_data->tex_no);
		cube_data->tex_no = NULL;
	}
	if (cube_data->tex_so)
	{
		mlx_delete_texture(cube_data->tex_so);
		cube_data->tex_so = NULL;
	}
	if (cube_data->tex_we)
	{
		mlx_delete_texture(cube_data->tex_we);
		cube_data->tex_we = NULL;
	}
	if (cube_data->tex_ea)
	{
		mlx_delete_texture(cube_data->tex_ea);
		cube_data->tex_ea = NULL;
	}
}

static void	free_paths(t_cube_data *cube_data)
{
	free(cube_data->no_path);
	free(cube_data->so_path);
	free(cube_data->we_path);
	free(cube_data->ea_path);
	cube_data->no_path = NULL;
	cube_data->so_path = NULL;
	cube_data->we_path = NULL;
	cube_data->ea_path = NULL;
}

static void	free_map_data(t_cube_data *cube_data)
{
	int			row;

	if (!cube_data->map)
		return ;
	row = 0;
	while (row < cube_data->map_height)
	{
		free(cube_data->map[row]);
		row++;
	}
	free(cube_data->map);
	cube_data->map = NULL;
}

void	free_all(t_cube_data *cube_data)
{
	if (!cube_data)
		return ;
	free_textures(cube_data);
	free_paths(cube_data);
	free_map_data(cube_data);
}
