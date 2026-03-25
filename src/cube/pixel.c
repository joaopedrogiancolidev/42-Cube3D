/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeneze <armeneze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:34:50 by arthur            #+#    #+#             */
/*   Updated: 2026/03/25 13:51:56 by armeneze         ###   ########.fr       */
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

	y = raycast->drawStart;
	while (y <= raycast->drawEnd)
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
	uint32_t	color;
	t_cube_data	*cube_data;
	int			y;
	int			x;

	color = ft_pixel(225, 30, 0, 255);
	cube_data = param;
	y = 0;
	x = 0;
	while (y < cube_data->image_cube.height)
	{
		x = 0;
		while (x < cube_data->image_cube.width)
		{
			if (y > cube_data->image_cube.height / 2)
				color = ft_pixel(220, 100, 0, 255);
			mlx_put_pixel(cube_data->image_cube.image, x, y, color);
			x ++;
		}
		y ++;
	}
}
