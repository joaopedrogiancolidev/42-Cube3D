/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:48:42 by arthur            #+#    #+#             */
/*   Updated: 2026/04/01 10:02:39 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_all(t_cube_data *cube_data)
{
	int	i;

	if (!cube_data)
		return ;
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
	free(cube_data->no_path);
	free(cube_data->so_path);
	free(cube_data->we_path);
	free(cube_data->ea_path);
	cube_data->no_path = NULL;
	cube_data->so_path = NULL;
	cube_data->we_path = NULL;
	cube_data->ea_path = NULL;
	if (!cube_data->map)
		return ;
	i = 0;
	while (i < cube_data->map_height)
	{
		free(cube_data->map[i]);
		i++;
	}
	free(cube_data->map);
	cube_data->map = NULL;
}
