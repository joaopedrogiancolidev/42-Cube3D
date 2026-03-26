/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_point_view.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeneze <armeneze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:20:28 by arthur            #+#    #+#             */
/*   Updated: 2026/03/26 11:24:28 by armeneze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	key_rigth_move_point_view(t_cube_data *cube_data)
{
	t_raycast	*r;

	r = &cube_data->raycast;
	r->olddir_x = r->dir_x;
	r->dir_x = r->dir_x
		* cos(-r->move_speed) - r->dir_y * sin(-r->move_speed);
	r->dir_y = r->olddir_x
		* sin(-r->move_speed) + r->dir_y * cos(-r->move_speed);
	r->oldplane_x = r->plane_x;
	r->plane_x = r->plane_x
		* cos(-r->move_speed) - r->plane_y * sin(-r->move_speed);
	r->plane_y = r->oldplane_x
		* sin(-r->move_speed) + r->plane_y * cos(-r->move_speed);
}

void	key_left_move_point_view(t_cube_data *cube_data)
{
	t_raycast	*r;

	r = &cube_data->raycast;
	r->olddir_x = r->dir_x;
	r->dir_x = r->dir_x
		* cos(r->move_speed) - r->dir_y * sin(r->move_speed);
	r->dir_y = r->olddir_x
		* sin(r->move_speed) + r->dir_y * cos(r->move_speed);
	r->oldplane_x = r->plane_x;
	r->plane_x = r->plane_x
		* cos(r->move_speed) - r->plane_y * sin(r->move_speed);
	r->plane_y = r->oldplane_x
		* sin(r->move_speed) + r->plane_y * cos(r->move_speed);
}
