/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:01:49 by arthur            #+#    #+#             */
/*   Updated: 2026/03/19 11:11:55 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void init_mlx(t_cube_data *cube_data)
{
	cube_data->win_width = 900;
	cube_data->win_height = 900;
	if (!(cube_data->mlx = mlx_init(cube_data->win_width, cube_data->win_height, "game", true)))
	{
		printf("%s\n", mlx_strerror(mlx_errno));
		return ;
	}
}

mlx_image_t *create_image(mlx_t *mlx, uint32_t width, uint32_t height)
{
	mlx_image_t *image;
	image = mlx_new_image(mlx, width, height);
	if (!image)
	{
		printf("%s\n", mlx_strerror(mlx_errno));
	} else 
	{
		printf("image created\n");
	}
	return (image);
}
