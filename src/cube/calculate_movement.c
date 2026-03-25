/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_movement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeneze <armeneze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:45:12 by arthur            #+#    #+#             */
/*   Updated: 2026/03/25 16:23:17 by armeneze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	key_up_move_position(t_cube_data *cube_data)
{
	if (cube_data->map[(int)cube_data->raycast.pos_y][(int)
		(cube_data->raycast.pos_x + cube_data->raycast.dir_x
			* cube_data->raycast.move_speed)] == 0)
	{
		cube_data->raycast.pos_x += cube_data->raycast.dir_x
			* cube_data->raycast.move_speed;
	}
	if (cube_data->map[(int)(cube_data->raycast.pos_y + cube_data->raycast.dir_y
			* cube_data->raycast.move_speed)]
			[(int)cube_data->raycast.pos_x] == 0)
	{
		cube_data->raycast.pos_y += cube_data->raycast.dir_y
			* cube_data->raycast.move_speed;
	}
}

void	key_down_move_position(t_cube_data *cube_data)
{
	if (cube_data->map[(int)cube_data->raycast.pos_y][(int)
		(cube_data->raycast.pos_x - cube_data->raycast.dir_x
			* cube_data->raycast.move_speed)] == 0)
	{
		cube_data->raycast.pos_x -= cube_data->raycast.dir_x
			* cube_data->raycast.move_speed;
	}
	if (cube_data->map[(int)(cube_data->raycast.pos_y - cube_data->raycast.dir_y
			* cube_data->raycast.move_speed)]
			[(int)cube_data->raycast.pos_x] == 0)
	{
		cube_data->raycast.pos_y -= cube_data->raycast.dir_y
			* cube_data->raycast.move_speed;
	}
}

void	key_rigth_move_position(t_cube_data *cube_data)
{
	double	move_s;
	double	dir_x;
	double	dir_y;

	move_s = cube_data->raycast.move_speed;
	dir_x = cube_data->raycast.dir_x;
	dir_y = cube_data->raycast.dir_y;
	if (cube_data->map[(int)cube_data->raycast.pos_y]
		[(int)(cube_data->raycast.pos_x - dir_y * move_s)] == 0)
	{
		cube_data->raycast.pos_x -= dir_y * move_s;
	}
	if (cube_data->map[(int)(cube_data->raycast.pos_y + dir_x * move_s)]
		[(int)cube_data->raycast.pos_x] == 0)
	{
		cube_data->raycast.pos_y += dir_x * move_s;
	}
}

void	key_left_move_position(t_cube_data *cube_data)
{
	double	move_s;
	double	dir_x;
	double	dir_y;

	move_s = cube_data->raycast.move_speed;
	dir_x = cube_data->raycast.dir_x;
	dir_y = cube_data->raycast.dir_y;
	if (cube_data->map[(int)cube_data->raycast.pos_y]
		[(int)(cube_data->raycast.pos_x - dir_y * move_s)] == 0)
	{
		cube_data->raycast.pos_x += dir_y * move_s;
	}
	if (cube_data->map[(int)(cube_data->raycast.pos_y + dir_x * move_s)]
		[(int)cube_data->raycast.pos_x] == 0)
	{
		cube_data->raycast.pos_y -= dir_x * move_s;
	}
}

void	calculate_rotation_and_movement(t_cube_data *cube_data)
{
	mlx_t	*mlx;

	mlx = cube_data->mlx;
	cube_data->raycast.time = mlx_get_time();
	cube_data->raycast.frame_time = cube_data->raycast.time
		- cube_data->raycast.old_time;
	cube_data->raycast.old_time = cube_data->raycast.time;
	cube_data->raycast.move_speed = cube_data->raycast.frame_time * 5.0;
	cube_data->raycast.move_speed = cube_data->raycast.frame_time * 3.0;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		key_up_move_position(cube_data);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		key_down_move_position(cube_data);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		key_left_move_position(cube_data);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		key_rigth_move_position(cube_data);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		key_rigth_move_point_view(cube_data);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		key_left_move_point_view(cube_data);
}
