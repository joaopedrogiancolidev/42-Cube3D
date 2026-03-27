/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeneze <armeneze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:02:57 by arthur            #+#    #+#             */
/*   Updated: 2026/03/27 09:48:51 by armeneze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void calculate_minimap_position(t_cube_data *cube_data)
{
	mlx_t		*mlx;
	t_raycast	*r;

	r = &cube_data->raycast;
	mlx = cube_data->mlx;

	printf("%d pos y \n", r->pos_y);
	printf("%d intance y \n", cube_data->player.image->instances[0].y);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		cube_data->player.image->instances[0].y -= r->pos_y / 4;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		cube_data->player.image->instances[0].y += r->pos_y / 4;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		cube_data->player.image->instances[0].x += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		cube_data->player.image->instances[0].x -= 5;
}
void	raycast(void *param)
{
	t_cube_data	*cube_data;
	mlx_t		*mlx;

	cube_data = param;
	mlx = cube_data->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_SPACE))
	{
		// implementação para logica de portas
		cube_data->map[8][8] = 0;
		printf("cube_data->map[8][8] = %d\n", cube_data->map[8][8]);
	}
	refresh_pixel(cube_data);
	calculate_raycast(cube_data);
	calculate_rotation_and_movement(cube_data);
	calculate_minimap_position(cube_data);
}


void ft_draw_minimap(t_cube_data *cube_data)
{
	uint32_t x;
	uint32_t y;
	uint32_t p_x;
	uint32_t p_y;
	uint32_t color;

	for (y = 0; y < 14; y++)
	{
		for (x = 0; x < 34; x++)
		{
			if (cube_data->map[y][x] == 1)
				color = ft_pixel(25, 109, 206, 255);
			else
				color = ft_pixel(0, 0, 0, 100);
			for (p_y = 0; p_y < 5; p_y++)
			{
				for (p_x = 0; p_x < 5; p_x++)
				{
					mlx_put_pixel(cube_data->minimap.image, 
								(x * 5) + p_x,
								(y * 5) + p_y,
								color);
				}
			}
		}
	}
}

void ft_draw_player(t_cube_data *cube_data)
{
	uint32_t x;
	uint32_t y;
	uint32_t p_x;
	uint32_t p_y;
	uint32_t color;

	for (y = 0; y < 5; y++)
	{
		for (x = 0; x < 5; x++)
		{
			color = ft_pixel(255, 255, 255, 255);
				mlx_put_pixel(cube_data->player.image, x, y,color);

		}
	}
}
int	start_cube(t_cube_data *cube_data)
{
	init_mlx(cube_data);
	if (!cube_data->mlx)
		return (EXIT_FAILURE);
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

	// cube_data->minimap.width = 200;
	// cube_data->minimap.height = 200;
	// cube_data->minimap.image = create_image(cube_data->mlx,
	// 		cube_data->minimap.width, cube_data->minimap.height);
	// if (!cube_data->minimap.image)
	// {
	// 	mlx_close_window(cube_data->mlx);
	// 	return (EXIT_FAILURE);
	// }
	// ft_draw_minimap(cube_data);
	// mlx_image_to_window(cube_data->mlx, cube_data->minimap.image, 20, 20);

	// cube_data->player.width = 5;
	// cube_data->player.height = 5;
	// cube_data->player.image = create_image(cube_data->mlx,
	// 		cube_data->player.width, cube_data->player.height);
	// if (!cube_data->player.image)
	// {
	// 	mlx_close_window(cube_data->mlx);
	// 	return (EXIT_FAILURE);
	// }
	// ft_draw_player(cube_data);
	// mlx_image_to_window(cube_data->mlx, cube_data->player.image, 35, 45);

	mlx_loop_hook(cube_data->mlx, raycast, cube_data);
	mlx_loop(cube_data->mlx);
	mlx_terminate(cube_data->mlx);
}
