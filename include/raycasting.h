/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeneze <armeneze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:05:01 by arthur            #+#    #+#             */
/*   Updated: 2026/03/27 10:59:38 by armeneze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

typedef struct s_cube_data	t_cube_data;
typedef struct s_raycast	t_raycast;

int			start_cube(t_cube_data *cube_data);
int32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void		calculate_raycast(t_cube_data *cube_data);
void		refresh_pixel(void *param);
void		calculate_rotation_and_movement(t_cube_data *cube_data);
void		key_rigth_move_point_view(t_cube_data *cube_data);
void		key_left_move_point_view(t_cube_data *cube_data);
void 		change_color(t_cube_data *cube_data, t_raycast *r);

#endif