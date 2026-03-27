/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeneze <armeneze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:42:12 by armeneze          #+#    #+#             */
/*   Updated: 2026/03/26 16:50:35 by armeneze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
