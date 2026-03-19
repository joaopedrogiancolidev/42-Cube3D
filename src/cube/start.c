/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:02:57 by arthur            #+#    #+#             */
/*   Updated: 2026/03/19 14:41:13 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


void raycast(void *param)
{
	t_cube_data* cube_data = param;
	mlx_t* mlx = cube_data->mlx;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	refresh_pixel(cube_data);
	calculate_hit(cube_data);
	calculate_rotation_and_movement(cube_data);
}

int start_cube(t_cube_data *cube_data)
{
	init_mlx(cube_data);
	if(!cube_data->mlx)
		return (EXIT_FAILURE);

	cube_data->image_cube.width = cube_data->mlx->width;
	cube_data->image_cube.height = cube_data->mlx->height;
	cube_data->image_cube.image = create_image(cube_data->mlx,
		cube_data->image_cube.width, cube_data->image_cube.height);
	if(!cube_data->image_cube.image)
	{
		mlx_close_window(cube_data->mlx);
		//////////// atenção /////////////////
		// caso a imagem não seja criada deve aver uma tratativa de erro
		return (EXIT_FAILURE);
	}
	mlx_image_to_window(cube_data->mlx, cube_data->image_cube.image, 0, 0);
	mlx_loop_hook(cube_data->mlx, raycast, cube_data);

	mlx_loop(cube_data->mlx);
	mlx_terminate(cube_data->mlx);
}
