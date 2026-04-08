/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:34:50 by arthur            #+#    #+#             */
/*   Updated: 2026/04/08 15:22:21 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ver_line(mlx_image_t	*img, int x, t_raycast *raycast)
{
	int	y;

	y = raycast->draw_start;
	while (y <= raycast->draw_end)
	{
		if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
		{
			mlx_put_pixel(img, x, y, raycast->color);
		}
		y++;
	}
}

void	refresh_pixel(void *param)
{
	t_cube_data	*cube_data;
	int			y;
	int			x;

	cube_data = param;
	y = 0;
	while (y < cube_data->image_cube.height)
	{
		x = 0;
		while (x < cube_data->image_cube.width)
		{
			if (y > (int)cube_data->image_cube.height / 2)
				mlx_put_pixel(cube_data->image_cube.image, x, y,
					ft_pixel(cube_data->floor_rgb[0], cube_data->floor_rgb[1],
						cube_data->floor_rgb[2], 255));
			else
				mlx_put_pixel(cube_data->image_cube.image, x, y,
					ft_pixel(cube_data->ceiling_rgb[0],
						cube_data->ceiling_rgb[1],
						cube_data->ceiling_rgb[2], 255));
			x ++;
		}
		y ++;
	}
}
