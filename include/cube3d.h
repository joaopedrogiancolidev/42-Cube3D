/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeneze <armeneze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 17:12:10 by arthur            #+#    #+#             */
/*   Updated: 2026/03/29 17:20:06 by armeneze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <MLX42/MLX42.h>
# include "image.h"
# include <stdint.h>
# include "raycasting.h"
# include <math.h>
# include "parser.h"

typedef struct s_image_cube
{
	mlx_image_t			*image;
	uint32_t			width;
	uint32_t			height;
}	t_image_cube;

typedef struct s_raycast
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		raydir_x;
	double		raydir_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	uint32_t	color;
	double		time;
	double		old_time;
	double		frame_time;
	double		move_speed;
	double		rot_speed;
	double		olddir_x;
	double		oldplane_x;	
}	t_raycast;

typedef struct s_data_minimap
{
	int	x;
	int	y;
	int	view_dist;
	int	map_x;
	int	map_y;
}	t_data_minimap;

typedef struct s_cube_data
{
	int				**map;
	int				map_width;
	int				map_height;
	int				win_width;
	int				win_height;
	t_image_cube	image_cube;
	mlx_image_t		*minimap;
	mlx_image_t		*player;
	t_raycast		raycast;
	mlx_t			*mlx;
}	t_cube_data;

int			parser(int argc, char **argv, t_cube_data *cube_data);
void		free_all(t_cube_data *cube_data);
void		ver_line(mlx_image_t	*img, int x, t_raycast *raycast);

#endif