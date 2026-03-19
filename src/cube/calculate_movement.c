/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_movement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:45:12 by arthur            #+#    #+#             */
/*   Updated: 2026/03/19 14:34:09 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	key_up_move_position(t_cube_data *cube_data)
{
	if(cube_data->map[(int)cube_data->raycast.posY][(int)
		(cube_data->raycast.posX + cube_data->raycast.dirX *
		cube_data->raycast.moveSpeed)] == 0)
	{
		cube_data->raycast.posX += cube_data->raycast.dirX *
		cube_data->raycast.moveSpeed;
	}
	if(cube_data->map[(int)(cube_data->raycast.posY + cube_data->raycast.dirY *
		cube_data->raycast.moveSpeed)][(int)cube_data->raycast.posX] == 0)
	{
		cube_data->raycast.posY += cube_data->raycast.dirY *
		cube_data->raycast.moveSpeed;
	}
}

void key_down_move_position(t_cube_data *cube_data)
{
	if(cube_data->map[(int)cube_data->raycast.posY][(int)
		(cube_data->raycast.posX - cube_data->raycast.dirX *
		cube_data->raycast.moveSpeed)] == 0)
	{
		cube_data->raycast.posX -= cube_data->raycast.dirX *
		cube_data->raycast.moveSpeed;
	}
	if(cube_data->map[(int)(cube_data->raycast.posY - cube_data->raycast.dirY *
		cube_data->raycast.moveSpeed)][(int)cube_data->raycast.posX] == 0)
	{
		cube_data->raycast.posY -= cube_data->raycast.dirY *
		cube_data->raycast.moveSpeed;
	}
}

void	key_rigth_move_position(t_cube_data *cube_data)
{
	double moveS;
	double dirX;
	double dirY;

	moveS = cube_data->raycast.moveSpeed;
	dirX = cube_data->raycast.dirX;
	dirY = cube_data->raycast.dirY;
	if (cube_data->map[(int)cube_data->raycast.posY][(int)(cube_data->raycast.posX 
		- dirY * moveS)] == 0)
	{
		cube_data->raycast.posX -= dirY * moveS;
	}
	if (cube_data->map[(int)(cube_data->raycast.posY + dirX * moveS)]
		[(int)cube_data->raycast.posX] == 0)
	{
		cube_data->raycast.posY += dirX * moveS;
	}
}

void	key_left_move_position(t_cube_data *cube_data)
{
	double moveS;
	double dirX;
	double dirY;

	moveS = cube_data->raycast.moveSpeed;
	dirX = cube_data->raycast.dirX;
	dirY = cube_data->raycast.dirY;
	if (cube_data->map[(int)cube_data->raycast.posY][(int)(cube_data->raycast.posX 
		- dirY * moveS)] == 0)
	{
		cube_data->raycast.posX += dirY * moveS;
	}
	if (cube_data->map[(int)(cube_data->raycast.posY + dirX * moveS)]
		[(int)cube_data->raycast.posX] == 0)
	{
		cube_data->raycast.posY -= dirX * moveS;
	}
}


void calculate_rotation_and_movement(t_cube_data *cube_data)
{
	mlx_t* mlx;

	mlx = cube_data->mlx;
	cube_data->raycast.time = mlx_get_time();
	cube_data->raycast.frameTime = cube_data->raycast.time - cube_data->raycast.oldTime;
	cube_data->raycast.oldTime = cube_data->raycast.time;
	cube_data->raycast.moveSpeed = cube_data->raycast.frameTime * 5.0; 
	cube_data->raycast.moveSpeed = cube_data->raycast.frameTime * 3.0;
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
