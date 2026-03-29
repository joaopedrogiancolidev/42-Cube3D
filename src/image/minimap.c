/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeneze <armeneze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 14:05:05 by armeneze          #+#    #+#             */
/*   Updated: 2026/03/29 15:17:28 by armeneze         ###   ########.fr       */
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
			mlx_put_pixel(cube_data->minimap, (x * half_width) + i
				, (y * half_height) + j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_cube_data *cube_data)
{
	int	x;
	int	y;

	y = 0;
	while (y < cube_data->map_height)
	{
		x = 0;
		while (x < cube_data->map_width)
		{
			if (cube_data->map[y][x] == 0)
				draw_square(cube_data, x, y, ft_pixel(255, 255, 255, 255));
			else
				draw_square(cube_data, x, y, ft_pixel(0, 0, 0, 255));
			x ++;
		}
		y ++;
	}
}

void	refresh_pixel_mimimap(t_cube_data *cube_data)
{
	uint32_t	color;
	int			y;
	int			x;

	color = ft_pixel(0, 0, 0, 255);
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

void    draw_moving_minimap(t_cube_data *cube_data)
{
    int x;
    int y;
    int view_dist = 5; // Quantos blocos ver para cada lado (total 11x11)
    int map_x;
    int map_y;

    y = 0;
	refresh_pixel_mimimap(cube_data);
    while (y < (view_dist * 2 + 1))
    {
        x = 0;
        while (x < (view_dist * 2 + 1))
        {
            // Calcula qual coordenada do mapa real corresponde a esse pixel do minimapa
            map_x = (int)cube_data->raycast.pos_x - view_dist + x;
            map_y = (int)cube_data->raycast.pos_y - view_dist + y;

            // 1. Verifica se está fora dos limites do mapa real (desenha vazio ou parede)
            if (map_y < 0 || map_y >= cube_data->map_height || 
                map_x < 0 || map_x >= cube_data->map_width)
                draw_square(cube_data, x, y, ft_pixel(50, 50, 50, 255)); // Cor de "fora do mapa"
            // 2. Se for parede
            else if (cube_data->map[map_y][map_x] == 1)
                draw_square(cube_data, x, y, ft_pixel(0, 0, 0, 255));
            // 3. Se for chão
            else
                draw_square(cube_data, x, y, ft_pixel(255, 255, 255, 255));
            x++;
        }
        y++;
    }
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

		cube_data->player = create_image(cube_data->mlx,5, 5);
	if (!cube_data->player)
	{
		mlx_close_window(cube_data->mlx);
		return (EXIT_FAILURE);
	}
	int x = 0;
	int y = 0;
	while (x < 3)
	{
		y = 0;
		while (y < 3)
		{
			mlx_put_pixel(cube_data->player, x, y, ft_pixel(255, 255, 255, 255));
			y++;
		}
		x++;
	}
	mlx_image_to_window(cube_data->mlx, cube_data->player, 20, 20);
	
	return (EXIT_SUCCESS);
}
