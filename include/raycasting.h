/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:05:01 by arthur            #+#    #+#             */
/*   Updated: 2026/03/19 11:08:04 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
#define RAYCASTING_H

typedef struct s_cube_data t_cube_data;


int start_cube(t_cube_data *cube_data);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

#endif