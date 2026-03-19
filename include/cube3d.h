/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 17:12:10 by arthur            #+#    #+#             */
/*   Updated: 2026/03/19 10:19:29 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
#define CUBE3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <MLX42/MLX42.h>
# include "image.h"
# include <stdint.h>

typedef struct s_image_cube
{
	mlx_image_t*	image;
	uint32_t			width;
	uint32_t			height;
}	t_image_cube;

typedef struct s_cube_data
{
	int 	map[24][24];
	int		map_width;
	int		map_height;
	int		win_width;
	int		win_height;
	float	player_x;
	float	player_y;
	float	player_angle;
	t_image_cube image_cube;
	mlx_t*	mlx;
}	t_cube_data;

t_cube_data parser(int argc, char **argv);
t_cube_data open_file_array(char *path);
void 		free_all(t_cube_data *cube_data);

#endif