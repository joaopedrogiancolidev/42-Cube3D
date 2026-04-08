/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 14:05:48 by armeneze          #+#    #+#             */
/*   Updated: 2026/04/08 14:10:31 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	create_image_cube(t_cube_data *cube_data)
{
	cube_data->image_cube.width = cube_data->mlx->width;
	cube_data->image_cube.height = cube_data->mlx->height;
	cube_data->image_cube.image = create_image(cube_data->mlx,
			cube_data->image_cube.width, cube_data->image_cube.height);
	if (!cube_data->image_cube.image)
	{
		mlx_close_window(cube_data->mlx);
		return (EXIT_FAILURE);
	}
	mlx_image_to_window(cube_data->mlx, cube_data->image_cube.image, 0, 0);
	return (EXIT_SUCCESS);
}
