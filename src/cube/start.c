/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:02:57 by arthur            #+#    #+#             */
/*   Updated: 2026/03/19 13:20:44 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>
#include <math.h>

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
void verLine(mlx_image_t* img, int x, int Start, int End, uint32_t color)
{
    int y = Start;

    while (y <= End)
    {
        if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
        {
            mlx_put_pixel(img, x, y, color);
        }
        y++;
    }
}
void refresh_pixel(void* param)
{
    uint32_t color;
	t_cube_data* cube_data;
    int y;
    int x;
    
    color = ft_pixel(225, 30, 0, 255);
    cube_data = param;
    y = 0;
    x = 0;
    while(y < cube_data->image_cube.height)
    {
        x = 0;
        while(x < cube_data->image_cube.width)
        {
            if(y > cube_data->image_cube.height / 2)
                color = ft_pixel(220, 100, 0, 255);
            mlx_put_pixel(cube_data->image_cube.image, x, y, color);
            x ++;
        }
        y ++;
    }
}
void raycast(void *param)
{
    
    t_cube_data* cube_data = param;
	mlx_image_t* image = cube_data->image_cube.image;
    mlx_t* mlx = cube_data->mlx;

	refresh_pixel(cube_data);
    for(int x = 0; x < cube_data->image_cube.width; x++)
    {
        cube_data->raycast.cameraX = 2 * x / (double)cube_data->image_cube.width - 1;
        cube_data->raycast.rayDirX = cube_data->raycast.dirX + cube_data->raycast.planeX * cube_data->raycast.cameraX;
        cube_data->raycast.rayDirY = cube_data->raycast.dirY + cube_data->raycast.planeY * cube_data->raycast.cameraX;

        cube_data->raycast.mapX = (int)cube_data->raycast.posX;
        cube_data->raycast.mapY = (int)cube_data->raycast.posY;

        cube_data->raycast.deltaDistX = (cube_data->raycast.rayDirX == 0) ? 1e30 : fabs(1 / cube_data->raycast.rayDirX);
        cube_data->raycast.deltaDistY = (cube_data->raycast.rayDirY == 0) ? 1e30 : fabs(1 / cube_data->raycast.rayDirY);

        if(cube_data->raycast.rayDirX < 0) {
            cube_data->raycast.stepX = -1;
            cube_data->raycast.sideDistX = (cube_data->raycast.posX - cube_data->raycast.mapX) * cube_data->raycast.deltaDistX;
        } else {
            cube_data->raycast.stepX = 1;
            cube_data->raycast.sideDistX = (cube_data->raycast.mapX + 1.0 - cube_data->raycast.posX) * cube_data->raycast.deltaDistX;
        }
        if(cube_data->raycast.rayDirY < 0) {
            cube_data->raycast.stepY = -1;
            cube_data->raycast.sideDistY = (cube_data->raycast.posY - cube_data->raycast.mapY) * cube_data->raycast.deltaDistY;
        } else {
            cube_data->raycast.stepY = 1;
            cube_data->raycast.sideDistY = (cube_data->raycast.mapY + 1.0 - cube_data->raycast.posY) * cube_data->raycast.deltaDistY;
        }

        cube_data->raycast.hit = 0;
        while(cube_data->raycast.hit == 0) {
            if(cube_data->raycast.sideDistX < cube_data->raycast.sideDistY) {
                cube_data->raycast.sideDistX += cube_data->raycast.deltaDistX;
                cube_data->raycast.mapX += cube_data->raycast.stepX;
                cube_data->raycast.side = 0;
            } else {
                cube_data->raycast.sideDistY += cube_data->raycast.deltaDistY;
                cube_data->raycast.mapY += cube_data->raycast.stepY;
                cube_data->raycast.side = 1;
            }
            if (cube_data->raycast.mapY >= 0 && cube_data->raycast.mapY < cube_data->map_height && cube_data->raycast.mapX >= 0 && cube_data->raycast.mapX < cube_data->map_width) {
                if(cube_data->map[cube_data->raycast.mapY][cube_data->raycast.mapX] > 0) cube_data->raycast.hit = 1; // [Y][X] Correto
            } else break;
        }
        if(cube_data->raycast.side == 0) cube_data->raycast.perpWallDist = (cube_data->raycast.sideDistX - cube_data->raycast.deltaDistX);
        else          cube_data->raycast.perpWallDist = (cube_data->raycast.sideDistY - cube_data->raycast.deltaDistY);

        cube_data->raycast.lineHeight = (int)(cube_data->image_cube.height / cube_data->raycast.perpWallDist);

        cube_data->raycast.drawStart = -cube_data->raycast.lineHeight / 2 + cube_data->image_cube.height / 2;
        if(cube_data->raycast.drawStart < 0) cube_data->raycast.drawStart = 0;
        cube_data->raycast.drawEnd = cube_data->raycast.lineHeight / 2 + cube_data->image_cube.height / 2;
        if(cube_data->raycast.drawEnd >= cube_data->image_cube.height) cube_data->raycast.drawEnd = cube_data->image_cube.height - 1;
        switch(cube_data->map[cube_data->raycast.mapY][cube_data->raycast.mapX])
        {
            case 1:  cube_data->raycast.color = ft_pixel(255, 0, 0, 255);    break;
            case 2:  cube_data->raycast.color = ft_pixel(0, 255, 0, 255);    break;
            case 3:  cube_data->raycast.color = ft_pixel(0, 0, 255, 255);    break;
            default: cube_data->raycast.color = ft_pixel(255, 255, 255, 255); break;
        }
        if(cube_data->raycast.side == 1) cube_data->raycast.color = (cube_data->raycast.color >> 1) & 0x7F7F7FFF;
        verLine(image, x, cube_data->raycast.drawStart, cube_data->raycast.drawEnd, cube_data->raycast.color);
    }

    double time = mlx_get_time(); 
    static double oldTime = 0;
    double frameTime = time - oldTime;
    oldTime = time;

    double moveSpeed = frameTime * 5.0; 
    double rotSpeed = frameTime * 3.0;

    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);    
    // --- ENTRADA DE TECLADO (Usando as variáveis static posX/cube_data->raycast.posY) ---
    if (mlx_is_key_down(mlx, MLX_KEY_UP)) {
        if(cube_data->map[(int)cube_data->raycast.posY][(int)(cube_data->raycast.posX + cube_data->raycast.dirX * moveSpeed)] == 0) cube_data->raycast.posX += cube_data->raycast.dirX * moveSpeed;
        if(cube_data->map[(int)(cube_data->raycast.posY + cube_data->raycast.dirY * moveSpeed)][(int)cube_data->raycast.posX] == 0) cube_data->raycast.posY += cube_data->raycast.dirY * moveSpeed;
    }
    if (mlx_is_key_down(mlx, MLX_KEY_DOWN)) {
        if(cube_data->map[(int)cube_data->raycast.posY][(int)(cube_data->raycast.posX - cube_data->raycast.dirX * moveSpeed)] == 0) cube_data->raycast.posX -= cube_data->raycast.dirX * moveSpeed;
        if(cube_data->map[(int)(cube_data->raycast.posY - cube_data->raycast.dirY * moveSpeed)][(int)cube_data->raycast.posX] == 0) cube_data->raycast.posY -= cube_data->raycast.dirY * moveSpeed;
    }

    // Rotação (Atrás do cálculo do Raycast para o próximo frame)
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT)) {
        double oldDirX = cube_data->raycast.dirX;
        cube_data->raycast.dirX = cube_data->raycast.dirX * cos(-rotSpeed) - cube_data->raycast.dirY * sin(-rotSpeed);
        cube_data->raycast.dirY = oldDirX * sin(-rotSpeed) + cube_data->raycast.dirY * cos(-rotSpeed);
        double oldPlaneX = cube_data->raycast.planeX;
        cube_data->raycast.planeX = cube_data->raycast.planeX * cos(-rotSpeed) - cube_data->raycast.planeY * sin(-rotSpeed);
        cube_data->raycast.planeY = oldPlaneX * sin(-rotSpeed) + cube_data->raycast.planeY * cos(-rotSpeed);
    }
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT)) {
        double oldDirX = cube_data->raycast.dirX;
        cube_data->raycast.dirX = cube_data->raycast.dirX * cos(rotSpeed) - cube_data->raycast.dirY * sin(rotSpeed);
        cube_data->raycast.dirY = oldDirX * sin(rotSpeed) + cube_data->raycast.dirY * cos(rotSpeed);
        double oldPlaneX = cube_data->raycast.planeX;
        cube_data->raycast.planeX = cube_data->raycast.planeX * cos(rotSpeed) - cube_data->raycast.planeY * sin(rotSpeed);
        cube_data->raycast.planeY = oldPlaneX * sin(rotSpeed) + cube_data->raycast.planeY * cos(rotSpeed);
    }
}

int start_cube(t_cube_data *cube_data)
{
	init_mlx(cube_data);
	if(!cube_data->mlx)
		return (EXIT_FAILURE);
	cube_data->image_cube.width = cube_data->mlx->width;
	cube_data->image_cube.height = cube_data->mlx->height;
	cube_data->image_cube.image = create_image(cube_data->mlx,
		cube_data->image_cube.width, cube_data->image_cube.height);
	if(!cube_data->image_cube.image)
	{
		mlx_close_window(cube_data->mlx);
		//////////// atenção /////////////////
		// caso a imagem não seja criada deve aver uma tratativa de erro
		return (EXIT_FAILURE);
	}
	mlx_image_to_window(cube_data->mlx, cube_data->image_cube.image, 0, 0);
	mlx_loop_hook(cube_data->mlx, raycast, cube_data);

	mlx_loop(cube_data->mlx);
	mlx_terminate(cube_data->mlx);
}
