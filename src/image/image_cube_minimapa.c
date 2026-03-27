/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_cube_minimapa.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeneze <armeneze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 11:01:42 by armeneze          #+#    #+#             */
/*   Updated: 2026/03/27 11:06:22 by armeneze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void ft_draw_minimap(t_cube_data *cube_data)
{
    uint32_t x;
    uint32_t y;
    uint32_t p_x;
    uint32_t p_y;
    uint32_t color;

    for (y = 0; y < 14; y++) // Percorre as linhas
    {
        for (x = 0; x < 34; x++) // Percorre as colunas
        {
            // 1. Define a cor baseada no valor do mapa
            if (cube_data->map[y][x] == 1)
                color = ft_pixel(255, 0, 0, 255);
            else if (cube_data->map[y][x] == 0)
                color = ft_pixel(0, 0, 0, 255); // Espaço vazio preto
            else
                color = ft_pixel(255, 255, 255, 255);

            // 2. Desenha o bloco de 20x20 na posição CORRETA
            // O segredo está em somar o (índice * tamanho_do_bloco)
            for (p_y = 0; p_y < 20; p_y++)
            {
                for (p_x = 0; p_x < 20; p_x++)
                {
                    mlx_put_pixel(cube_data->minimap.image, 
                                  (x * 20) + p_x, 
                                  (y * 20) + p_y, 
                                  color);
                }
            }
        }
    }
}

int	create_image_cube_minimap(t_cube_data *cube_data)
{
	cube_data->image_cube.width = cube_data->mlx->width;
	cube_data->image_cube.height = cube_data->mlx->height;
	cube_data->image_cube.image = create_image(cube_data->mlx,
			cube_data->image_cube.width, cube_data->image_cube.height);
	if (!cube_data->image_cube.image)
	{
		mlx_close_window(cube_data->mlx);
		return (EXIT_FAILURE);
	}
	mlx_image_to_window(cube_data->mlx, cube_data->minimap.image, 0, 0);
	cube_data->minimap.width = 90;
	cube_data->minimap.height = 90;
	cube_data->minimap.image = create_image(cube_data->mlx,
			cube_data->minimap.width, cube_data->minimap.height);
	if (!cube_data->minimap.image)
	{
		mlx_close_window(cube_data->mlx);
		return (EXIT_FAILURE);
	}
	ft_draw_minimap(cube_data);
	mlx_image_to_window(cube_data->mlx, cube_data->minimap.image, 20, 20);
	return (0);
}
