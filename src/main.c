/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:57:22 by arthur            #+#    #+#             */
/*   Updated: 2026/03/19 10:45:07 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include "cube3d.h"


#define WIDTH 512
#define HEIGHT 512


// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void *param)
{
	mlx_image_t* image = param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

// void ft_hook(t_cube_data *param)
// {
// 	mlx_t* mlx = param->mlx;
// 	mlx_image_t* image = param->image_cube->image;

// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP))
// 		image.instances[0].y -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
// 		image.instances[0].y += 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
// 		image.instances[0].x -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		image.instances[0].x += 5;
// }

void draw_image(void *param)
{
	mlx_image_t* image_cube = param;
	for (uint32_t i = 0; i < image_cube->image->width; ++i)
	{
		for (uint32_t y = 0; y < image_cube->image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image_cube->image, i, y, color);
		}
	}
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
		// caso a imagem não seja criada deve aver uma tratatica de erro
		return (EXIT_FAILURE);
	}
	draw_image(&cube_data->image_cube);
	mlx_image_to_window(cube_data->mlx, cube_data->image_cube.image, 0, 0);
	// mlx_loop_hook(cube_data->mlx, ft_randomize, &cube_data->image_cube);
	// mlx_loop_hook(cube_data->mlx, ft_hook, &cube_data);

	mlx_loop(cube_data->mlx);
	mlx_terminate(cube_data->mlx);
}
int main(int argc, char **argv)
{
	t_cube_data cube_data;
	
	cube_data = parser(argc, argv);
	if(start_cube(&cube_data) > 0)
	{
		printf("error\n");
	}
	free_all(&cube_data);
	return (0);
}
