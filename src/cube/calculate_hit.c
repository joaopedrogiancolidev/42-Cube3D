#include "cube3d.h"


void	calculate_dda(t_cube_data* cube_data, int x)
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
}
void	calculate_hit(t_cube_data* cube_data)
{
	int x;

	x = 0;
	while (x < cube_data->image_cube.width)
	{
		calculate_dda(cube_data, x);
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
		verLine(cube_data->image_cube.image, x, cube_data->raycast.drawStart, cube_data->raycast.drawEnd, cube_data->raycast.color);
		x++;
	}
}
