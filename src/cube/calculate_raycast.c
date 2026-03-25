/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeneze <armeneze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:01:18 by armeneze          #+#    #+#             */
/*   Updated: 2026/03/25 16:04:07 by armeneze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


void	calculate_side_dist(t_raycast *r)
{
	if (r->rayDirX < 0)
	{
		r->stepX = -1;
		r->sideDistX = (r->posX - r->mapX) * r->deltaDistX;
	}
	else
	{
		r->stepX = 1;
		r->sideDistX = (r->mapX + 1.0 - r->posX) * r->deltaDistX;
	}
	if (r->rayDirY < 0)
	{
		r->stepY = -1;
		r->sideDistY = (r->posY - r->mapY) * r->deltaDistY;
	}
	else
	{
		r->stepY = 1;
		r->sideDistY = (r->mapY + 1.0 - r->posY) * r->deltaDistY;
	}
}

void	calculate_dda(t_cube_data *cube_data, int x)
{
	t_raycast	*r;

	r = &cube_data->raycast;
	r->cameraX = 2 * x / (double)cube_data->image_cube.width - 1;
	r->rayDirX = r->dirX + r->planeX * r->cameraX;
	r->rayDirY = r->dirY + r->planeY * r->cameraX;
	r->mapX = (int)r->posX;
	r->mapY = (int)r->posY;
	if (r->rayDirX == 0)
		r->deltaDistX = 1e30;
	else
		r->deltaDistX = fabs(1 / r->rayDirX);
	if (r->rayDirY == 0)
		r->deltaDistY = 1e30;
	else
		r->deltaDistY = fabs(1 / r->rayDirY);
	calculate_side_dist(r);
}

uint32_t	change_color(t_cube_data *cube_data, t_raycast *r)
{
	if (cube_data->map[r->mapY][r->mapX] == 1)
		r->color = ft_pixel(255, 0, 0, 255);
	else if (cube_data->map[r->mapY][r->mapX] == 2)
		r->color = ft_pixel(0, 255, 0, 255);
	else if (cube_data->map[r->mapY][r->mapX] == 3)
		r->color = ft_pixel(0, 0, 255, 255);
	else
		r->color = ft_pixel(255, 255, 255, 255);
	if (r->side == 1)
		r->color = (r->color >> 1) & 0x7F7F7FFF;
}

void	calculate_hit(t_raycast *r, t_cube_data *cube_data)
{
	r->hit = 0;
	while (r->hit == 0)
	{
		if (r->sideDistX < r->sideDistY)
		{
			r->sideDistX += r->deltaDistX;
			r->mapX += r->stepX;
			r->side = 0;
		}
		else
		{
			r->sideDistY += r->deltaDistY;
			r->mapY += r->stepY;
			r->side = 1;
		}
		if (r->mapY >= 0 && r->mapY < cube_data->map_height && r->mapX >= 0
			&& r->mapX < cube_data->map_width)
		{
			if (cube_data->map[r->mapY][r->mapX] > 0)
				r->hit = 1;
		}
		else
			break ;
	}
}

void	calculate_raycast(t_cube_data *cube_data)
{
	int			x;
	t_raycast	*r;

	r = &cube_data->raycast;
	x = 0;
	while (x < cube_data->image_cube.width)
	{
		calculate_dda(cube_data, x);
		calculate_hit(r, cube_data);
		if (r->side == 0)
			r->perpWallDist = (r->sideDistX - r->deltaDistX);
		else
			r->perpWallDist = (r->sideDistY - r->deltaDistY);
		r->lineHeight = (int)(cube_data->image_cube.height / r->perpWallDist);
		r->drawStart = -r->lineHeight / 2 + cube_data->image_cube.height / 2;
		if (r->drawStart < 0)
			r->drawStart = 0;
		r->drawEnd = r->lineHeight / 2 + cube_data->image_cube.height / 2;
		if (r->drawEnd >= cube_data->image_cube.height)
			r->drawEnd = cube_data->image_cube.height - 1;
		change_color(cube_data, r);
		ver_line(cube_data->image_cube.image, x, &cube_data->raycast);
		x++;
	}
}
