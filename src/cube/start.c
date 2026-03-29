/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeneze <armeneze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:02:57 by arthur            #+#    #+#             */
/*   Updated: 2026/03/28 20:48:09 by armeneze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// void	calculate_movemente_player_minimap(t_cube_data *cube_data)
// {
// 	t_raycast	*r;

// 	r = &cube_data->raycast;
	
	
// 	cube_data->player.image->instances[0].x = r->pos_x * 5 + 20;
// 	cube_data->player.image->instances[0].y = r->pos_y * 5 + 20;
// }

void calculate_movemente_player_minimap(t_cube_data *cube_data, double move_x, double move_y)
{
    t_raycast *r = &cube_data->raycast;

    // 1. Calcula a posição para onde o jogador QUER ir
    double next_x = r->pos_x + move_x;
    double next_y = r->pos_y + move_y;

    // 2. Verifica colisão no eixo X
    // O (int) converte a coordenada real para o índice da array do mapa
    if (cube_data->map[(int)r->pos_y][(int)next_x] == 0)
    {
        cube_data->player.image->instances[0].x = r->pos_x * 10 + 20;
    }

    // 3. Verifica colisão no eixo Y
    if (cube_data->map[(int)next_y][(int)r->pos_x] == 0)
    {
        cube_data->player.image->instances[0].y = r->pos_y * 10 + 19;
    }

    // 4. Só agora atualiza a imagem no minimapa
}

void	raycast(void *param)
{
	t_cube_data	*cube_data;
	mlx_t		*mlx;

	cube_data = param;
	mlx = cube_data->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	refresh_pixel(cube_data);
	calculate_raycast(cube_data);
	calculate_rotation_and_movement(cube_data);
	calculate_movemente_player_minimap(cube_data, 0.5 ,0.5);
}

int	start_cube(t_cube_data *cube_data)
{
	init_mlx(cube_data);
	if (!cube_data->mlx || create_image_cube_minimap(cube_data))
		return (EXIT_FAILURE);
	mlx_loop_hook(cube_data->mlx, raycast, cube_data);
	mlx_loop(cube_data->mlx);
	mlx_terminate(cube_data->mlx);
	return (0);
}
