/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_cube_minimap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeneze <armeneze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 11:01:42 by armeneze          #+#    #+#             */
/*   Updated: 2026/03/28 20:47:12 by armeneze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

uint32_t	change_color_minimap(t_cube_data *cube_data, int map_y, int map_x)
{
	if (cube_data->map[map_y][map_x] == 1)
		return (ft_pixel(137, 137, 137, 255));
	else if (cube_data->map[map_y][map_x] == 2)
		return (ft_pixel(0, 255, 0, 255));
	else if (cube_data->map[map_y][map_x] == 3)
		return (ft_pixel(0, 0, 255, 255));
	else
		return (ft_pixel(137, 137, 137, 100));

}

void	ft_draw_minimap(t_cube_data *cube_data)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	p_x;
	uint32_t	p_y;
	uint32_t	color;

	y = 0;
	while (y < cube_data->map_height)
	{
		x = 0;
		while (x < cube_data->map_width)
		{
			color = change_color_minimap(cube_data, y, x);
			p_y = 0;
			while (p_y < 20)
			{
				p_x = 0;
				while (p_x < 20)
				{
					mlx_put_pixel(cube_data->minimap.image
						, (x * 10) + p_x, (y * 10) + p_y, color);
					p_x ++;
				}
				p_y ++;
			}
			x ++;
		}
		y ++;
	}
}

void	ft_draw_player(t_cube_data *cube_data)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;

	y = 0;
	color = ft_pixel(255, 255, 255, 255);
	while (y < 5)
	{
		x = 0;
		while (x <= 5)
		{
			mlx_put_pixel(cube_data->player.image, x, y, color);
			x++;
		}
		y++;
	}
}

int	create_image_cube_minimap(t_cube_data *cube_data)
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

	cube_data->minimap.width = cube_data->map_width * 20;
	cube_data->minimap.height = cube_data->map_height * 20;
	cube_data->minimap.image = create_image(cube_data->mlx,
			cube_data->minimap.width, cube_data->minimap.height);
	if (!cube_data->minimap.image)
	{
		mlx_close_window(cube_data->mlx);
		return (EXIT_FAILURE);
	}
	ft_draw_minimap(cube_data);
	mlx_image_to_window(cube_data->mlx, cube_data->minimap.image, 20, 20);

	cube_data->player.width = 20;
	cube_data->player.height = 20;
	cube_data->player.image = create_image(cube_data->mlx,
			cube_data->player.width, cube_data->player.height);
	if (!cube_data->player.image)
	{
		mlx_close_window(cube_data->mlx);
		return (EXIT_FAILURE);
	}
	ft_draw_player(cube_data);
	mlx_image_to_window(cube_data->mlx, cube_data->player.image, cube_data->raycast.pos_x * 10 + 20,  cube_data->raycast.pos_y * 10 + 20);
	return (0);
}
