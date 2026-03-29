/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeneze <armeneze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:02:57 by arthur            #+#    #+#             */
/*   Updated: 2026/03/29 15:03:49 by armeneze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	raycast(void *param)
{
	t_cube_data	*cube_data;
	mlx_t		*mlx;

	cube_data = param;
	mlx = cube_data->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	refresh_pixel(cube_data);
	calculate_raycast(cube_data);
	calculate_rotation_and_movement(cube_data);
	ft_memset(cube_data->minimap->pixels, 0, cube_data->minimap->width * cube_data->minimap->height * sizeof(int));
	draw_moving_minimap(cube_data);
}

int	start_cube(t_cube_data *cube_data)
{
	init_mlx(cube_data);
	if (!cube_data->mlx || create_image_cube(cube_data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!cube_data->mlx || create_minimap(cube_data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	mlx_loop_hook(cube_data->mlx, raycast, cube_data);
	mlx_loop(cube_data->mlx);
	mlx_terminate(cube_data->mlx);
}
