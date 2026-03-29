/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeneze <armeneze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 14:05:05 by armeneze          #+#    #+#             */
/*   Updated: 2026/03/29 15:56:17 by armeneze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_square(t_cube_data *cube_data, int x, int y, uint32_t color)
{
	int	i;
	int	j;
	int	half_width;
	int	half_height;

	i = 0;
	half_width = cube_data->image_cube.width / 100;
	half_height = half_width;
	while (i < half_width)
	{
		j = 0;
		while (j < half_height)
		{
			mlx_put_pixel(cube_data->minimap, (x * half_width) + i,
				(y * half_height) + j, color);
			j++;
		}
		i++;
	}
}

void	refresh_pixel_mimimap(t_cube_data *cube_data)
{
	uint32_t	color;
	int			y;
	int			x;

	color = ft_pixel(0, 0, 0, 100);
	y = 0;
	x = 0;
	while (y < cube_data->minimap->height)
	{
		x = 0;
		while (x < cube_data->minimap->width)
		{
			mlx_put_pixel(cube_data->minimap, x, y, color);
			x ++;
		}
		y ++;
	}
}

void	draw_moving_minimap(t_cube_data *cube_data)
{
	t_data_minimap	m;

	m.view_dist = 5;
	m.y = 0;
	refresh_pixel_mimimap(cube_data);
	while (m.y < (m.view_dist * 2 + 1))
	{
		m.x = 0;
		while (m.x < (m.view_dist * 2 + 1))
		{
			m.map_x = (int)cube_data->raycast.pos_x - m.view_dist + m.x;
			m.map_y = (int)cube_data->raycast.pos_y - m.view_dist + m.y;
			if (m.map_y < 0 || m.map_y >= cube_data->map_height || m.map_x < 0
				|| m.map_x >= cube_data->map_width)
				draw_square(cube_data, m.x, m.y, ft_pixel(50, 50, 50, 255));
			else if (cube_data->map[m.map_y][m.map_x] == 1)
				draw_square(cube_data, m.x, m.y, ft_pixel(0, 0, 0, 255));
			else if (cube_data->map[m.map_y][m.map_x] == 2)
				draw_square(cube_data, m.x, m.y, ft_pixel(137, 0, 0, 255));
			else
				draw_square(cube_data, m.x, m.y, ft_pixel(255, 255, 255, 100));
			m.x++;
		}
		m.y++;
	}
}

int	player(t_cube_data *cube_data)
{
	int	x;
	int	y;

	cube_data->player = create_image(cube_data->mlx, 9, 9);
	if (!cube_data->player)
	{
		mlx_close_window(cube_data->mlx);
		return (EXIT_FAILURE);
	}
	x = 0;
	y = 0;
	while (x < 9)
	{
		y = 0;
		while (y < 9)
		{
			mlx_put_pixel(cube_data->player, x, y,
				ft_pixel(255, 255, 255, 255));
			y++;
		}
		x++;
	}
	mlx_image_to_window(cube_data->mlx, cube_data->player, 65, 65);
	return (EXIT_SUCCESS);
}

int	create_minimap(t_cube_data *cube_data)
{
	cube_data->minimap = create_image(cube_data->mlx,
			99, 99);
	if (!cube_data->minimap)
	{
		mlx_close_window(cube_data->mlx);
		return (EXIT_FAILURE);
	}
	draw_moving_minimap(cube_data);
	mlx_image_to_window(cube_data->mlx, cube_data->minimap, 20, 20);
	return (player(cube_data));
}
