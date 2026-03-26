/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_movement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:45:12 by arthur            #+#    #+#             */
/*   Updated: 2026/03/26 18:55:40 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	key_up_move_position(t_cube_data *cube_data)
{
	t_raycast	*r;

	r = &cube_data->raycast;
	if (cube_data->map[(int)r->pos_y]
		[(int)(r->pos_x + r->dir_x * r->move_speed)] == 0)
	{
		r->pos_x += r->dir_x * r->move_speed;
	}
	if (cube_data->map[(int)(r->pos_y + r->dir_y
			* r->move_speed)][(int)r->pos_x] == 0)
	{
		r->pos_y += r->dir_y * r->move_speed;
	}
}

void	key_down_move_position(t_cube_data *cube_data)
{
	t_raycast	*r;

	r = &cube_data->raycast;
	if (cube_data->map[(int)r->pos_y]
		[(int)(r->pos_x - r->dir_x * r->move_speed)] == 0)
	{
		r->pos_x -= r->dir_x * r->move_speed;
	}
	if (cube_data->map[(int)(r->pos_y - r->dir_y
			* r->move_speed)][(int)r->pos_x] == 0)
	{
		r->pos_y -= r->dir_y * r->move_speed;
	}
}

void	key_rigth_move_position(t_cube_data *cube_data)
{
	t_raycast	*r;

	r = &cube_data->raycast;
	if (cube_data->map[(int)r->pos_y]
		[(int)(r->pos_x - r->dir_y * r->move_speed)] == 0)
	{
		r->pos_x -= r->dir_y * r->move_speed;
	}
	if (cube_data->map[(int)(r->pos_y + r->dir_x * r->move_speed)]
		[(int)r->pos_x] == 0)
	{
		r->pos_y += r->dir_x * r->move_speed;
	}
}

void	key_left_move_position(t_cube_data *cube_data)
{
	t_raycast	*r;

	r = &cube_data->raycast;
	if (cube_data->map[(int)r->pos_y]
		[(int)(r->pos_x + r->dir_y * r->move_speed)] == 0)
	{
		r->pos_x += r->dir_y * r->move_speed;
	}
	if (cube_data->map[(int)(r->pos_y - r->dir_x * r->move_speed)]
		[(int)r->pos_x] == 0)
	{
		r->pos_y -= r->dir_x * r->move_speed;
	}
}

void	calculate_rotation_and_movement(t_cube_data *cube_data)
{
	mlx_t		*mlx;
	t_raycast	*r;

	r = &cube_data->raycast;
	mlx = cube_data->mlx;
	r->time = mlx_get_time();
	r->frame_time = r->time - r->old_time;
	r->old_time = r->time;
	r->move_speed = r->frame_time * 5.0;
	r->move_speed = r->frame_time * 3.0;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		key_up_move_position(cube_data);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		key_down_move_position(cube_data);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		key_left_move_position(cube_data);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		key_rigth_move_position(cube_data);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		key_rigth_move_point_view(cube_data);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		key_left_move_point_view(cube_data);
}
