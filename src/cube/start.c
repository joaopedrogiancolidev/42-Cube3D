/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:02:57 by arthur            #+#    #+#             */
/*   Updated: 2026/04/08 14:05:08 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	load_wall_textures(t_cube_data *cube_data)
{
	cube_data->tex_no = mlx_load_png(cube_data->no_path);
	if (!cube_data->tex_no)
	{
		printf("Error\nfailed to load NO texture: %s\n", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	cube_data->tex_so = mlx_load_png(cube_data->so_path);
	if (!cube_data->tex_so)
	{
		printf("Error\nfailed to load SO texture: %s\n", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	cube_data->tex_we = mlx_load_png(cube_data->we_path);
	if (!cube_data->tex_we)
	{
		printf("Error\nfailed to load WE texture: %s\n", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	cube_data->tex_ea = mlx_load_png(cube_data->ea_path);
	if (!cube_data->tex_ea)
	{
		printf("Error\nfailed to load EA texture: %s\n", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	door(mlx_key_data_t keydata, void *param)
{
	t_cube_data	*c;
	int			next_x;
	int			next_y;
	mlx_t		*mlx;

	c = (t_cube_data *)param;
	mlx = c->mlx;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		next_x = (int)(c->raycast.pos_x + c->raycast.dir_x * 1);
		next_y = (int)(c->raycast.pos_y + c->raycast.dir_y * 1);
		if (c->map[next_y][next_x] == 1)
		{
			c->map[next_y][next_x] = 3;
		}
		else if (c->map[next_y][next_x] == 3)
		{
			c->map[next_y][next_x] = 1;
		}
	}
}

void	raycast(void *param)
{
	t_cube_data	*c;
	mlx_t		*mlx;

	c = param;
	mlx = c->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	refresh_pixel(c);
	calculate_raycast(c);
	calculate_rotation_and_movement(c);
	ft_memset(c->minimap->pixels, 0,
		c->minimap->width * c->minimap->height * sizeof(int));
	draw_moving_minimap(c);
}

int	start_cube(t_cube_data *cube_data)
{
	init_mlx(cube_data);
	if (load_wall_textures(cube_data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!cube_data->mlx || create_image_cube(cube_data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!cube_data->mlx || create_minimap(cube_data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	mlx_key_hook(cube_data->mlx, &door, cube_data);
	mlx_loop_hook(cube_data->mlx, raycast, cube_data);
	mlx_loop(cube_data->mlx);
	mlx_terminate(cube_data->mlx);
	return (EXIT_SUCCESS);
}
