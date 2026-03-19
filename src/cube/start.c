/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:02:57 by arthur            #+#    #+#             */
/*   Updated: 2026/03/19 11:12:06 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void raycast(void *param)
{
	t_cube_data* cube_data = param;
	mlx_image_t* image = cube_data->image_cube.image;
	if (mlx_is_key_down(cube_data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cube_data->mlx);

	for (uint32_t i = 0; i < 128; ++i)
	{
		for (uint32_t y = 0; y < 128; ++y)
		{
			uint32_t color = ft_pixel(
				255, // R
				255, // G
				255, // B
				255  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
	if (mlx_is_key_down(cube_data->mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(cube_data->mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(cube_data->mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(cube_data->mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
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
