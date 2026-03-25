/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_raycast.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeneze <armeneze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:22:37 by armeneze          #+#    #+#             */
/*   Updated: 2026/03/25 16:22:56 by armeneze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	calculate_side_dist(t_raycast *r)
{
	if (r->raydir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (r->pos_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - r->pos_x) * r->delta_dist_x;
	}
	if (r->raydir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (r->pos_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - r->pos_y) * r->delta_dist_y;
	}
}

void	calculate_dda(t_cube_data *cube_data, int x)
{
	t_raycast	*r;

	r = &cube_data->raycast;
	r->camera_x = 2 * x / (double)cube_data->image_cube.width - 1;
	r->raydir_x = r->dir_x + r->plane_x * r->camera_x;
	r->raydir_y = r->dir_y + r->plane_y * r->camera_x;
	r->map_x = (int)r->pos_x;
	r->map_y = (int)r->pos_y;
	if (r->raydir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1 / r->raydir_x);
	if (r->raydir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1 / r->raydir_y);
	calculate_side_dist(r);
}

uint32_t	change_color(t_cube_data *cube_data, t_raycast *r)
{
	if (cube_data->map[r->map_y][r->map_x] == 1)
		r->color = ft_pixel(255, 0, 0, 255);
	else if (cube_data->map[r->map_y][r->map_x] == 2)
		r->color = ft_pixel(0, 255, 0, 255);
	else if (cube_data->map[r->map_y][r->map_x] == 3)
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
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_y >= 0 && r->map_y < cube_data->map_height && r->map_x >= 0
			&& r->map_x < cube_data->map_width)
		{
			if (cube_data->map[r->map_y][r->map_x] > 0)
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
			r->perp_wall_dist = (r->side_dist_x - r->delta_dist_x);
		else
			r->perp_wall_dist = (r->side_dist_y - r->delta_dist_y);
		r->line_height = (int)(cube_data->image_cube.height
				/ r->perp_wall_dist);
		r->draw_start = -r->line_height / 2 + cube_data->image_cube.height / 2;
		if (r->draw_start < 0)
			r->draw_start = 0;
		r->draw_end = r->line_height / 2 + cube_data->image_cube.height / 2;
		if (r->draw_end >= cube_data->image_cube.height)
			r->draw_end = cube_data->image_cube.height - 1;
		change_color(cube_data, r);
		ver_line(cube_data->image_cube.image, x, &cube_data->raycast);
		x++;
	}
}
