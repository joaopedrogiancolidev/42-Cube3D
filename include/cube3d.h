/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 17:12:10 by arthur            #+#    #+#             */
/*   Updated: 2026/03/18 17:32:13 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
#define CUBE3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <MLX42/MLX42.h>

typedef struct s_cube_data
{
	int **map;
	int map_width;
	int map_height;
	float player_x;
	float player_y;
	float player_angle;
}	t_cube_data;


t_cube_data parser(int argc, char **argv);
int **open_file_array(char *path);


#endif