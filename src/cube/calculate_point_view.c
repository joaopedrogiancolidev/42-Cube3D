/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_point_view.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeneze <armeneze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:20:28 by arthur            #+#    #+#             */
/*   Updated: 2026/03/25 16:23:27 by armeneze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	key_rigth_move_point_view(t_cube_data *cube_data)
{
	cube_data->raycast.olddir_x = cube_data->raycast.dir_x;
	cube_data->raycast.dir_x = cube_data->raycast.dir_x
		* cos(-cube_data->raycast.move_speed) - cube_data->raycast.dir_y
		* sin(-cube_data->raycast.move_speed);
	cube_data->raycast.dir_y = cube_data->raycast.olddir_x
		* sin(-cube_data->raycast.move_speed) + cube_data->raycast.dir_y
		* cos(-cube_data->raycast.move_speed);
	cube_data->raycast.oldplane_x = cube_data->raycast.plane_x;
	cube_data->raycast.plane_x = cube_data->raycast.plane_x
		* cos(-cube_data->raycast.move_speed) - cube_data->raycast.plane_y
		* sin(-cube_data->raycast.move_speed);
	cube_data->raycast.plane_y = cube_data->raycast.oldplane_x
		* sin(-cube_data->raycast.move_speed) + cube_data->raycast.plane_y
		* cos(-cube_data->raycast.move_speed);
}

void	key_left_move_point_view(t_cube_data *cube_data)
{
	cube_data->raycast.olddir_x = cube_data->raycast.dir_x;
	cube_data->raycast.dir_x = cube_data->raycast.dir_x
		* cos(cube_data->raycast.move_speed) - cube_data->raycast.dir_y
		* sin(cube_data->raycast.move_speed);
	cube_data->raycast.dir_y = cube_data->raycast.olddir_x
		* sin(cube_data->raycast.move_speed) + cube_data->raycast.dir_y
		* cos(cube_data->raycast.move_speed);
	cube_data->raycast.oldplane_x = cube_data->raycast.plane_x;
	cube_data->raycast.plane_x = cube_data->raycast.plane_x
		* cos(cube_data->raycast.move_speed) - cube_data->raycast.plane_y
		* sin(cube_data->raycast.move_speed);
	cube_data->raycast.plane_y = cube_data->raycast.oldplane_x
		* sin(cube_data->raycast.move_speed) + cube_data->raycast.plane_y
		* cos(cube_data->raycast.move_speed);
}
