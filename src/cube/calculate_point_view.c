/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_point_view.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:20:28 by arthur            #+#    #+#             */
/*   Updated: 2026/03/19 14:20:33 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void key_rigth_move_point_view(t_cube_data *cube_data)
{
	cube_data->raycast.oldDirX = cube_data->raycast.dirX;
	cube_data->raycast.dirX = cube_data->raycast.dirX *
	cos(-cube_data->raycast.moveSpeed) - cube_data->raycast.dirY *
	sin(-cube_data->raycast.moveSpeed);
	cube_data->raycast.dirY = cube_data->raycast.oldDirX *
	sin(-cube_data->raycast.moveSpeed) + cube_data->raycast.dirY *
	cos(-cube_data->raycast.moveSpeed);
	cube_data->raycast.oldPlaneX = cube_data->raycast.planeX;
	cube_data->raycast.planeX = cube_data->raycast.planeX *
	cos(-cube_data->raycast.moveSpeed) - cube_data->raycast.planeY *
	sin(-cube_data->raycast.moveSpeed);
	cube_data->raycast.planeY = cube_data->raycast.oldPlaneX *
	sin(-cube_data->raycast.moveSpeed) + cube_data->raycast.planeY *
	cos(-cube_data->raycast.moveSpeed);
}

void key_left_move_point_view(t_cube_data *cube_data)
{
	cube_data->raycast.oldDirX = cube_data->raycast.dirX;
	cube_data->raycast.dirX = cube_data->raycast.dirX *
	cos(cube_data->raycast.moveSpeed) - cube_data->raycast.dirY *
	sin(cube_data->raycast.moveSpeed);
	cube_data->raycast.dirY = cube_data->raycast.oldDirX *
	sin(cube_data->raycast.moveSpeed) + cube_data->raycast.dirY *
	cos(cube_data->raycast.moveSpeed);
	cube_data->raycast.oldPlaneX = cube_data->raycast.planeX;
	cube_data->raycast.planeX = cube_data->raycast.planeX *
	cos(cube_data->raycast.moveSpeed) - cube_data->raycast.planeY *
	sin(cube_data->raycast.moveSpeed);
	cube_data->raycast.planeY = cube_data->raycast.oldPlaneX *
	sin(cube_data->raycast.moveSpeed) + cube_data->raycast.planeY *
	cos(cube_data->raycast.moveSpeed);
}