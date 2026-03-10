#include "visual.h"

#include <MLX42/MLX42.h>

#define CELL_SIZE 32

static int	is_walkable(char cell)
{
	return (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W');
}

static int	is_open_cell(const t_map_grid *map_grid, size_t x, size_t y)
{
	if (!is_walkable(map_grid->rows[y][x]))
		return (0);
	if (x == 0 || y == 0 || x + 1 == map_grid->width || y + 1 == map_grid->height)
		return (1);
	if (map_grid->rows[y][x - 1] == ' ' || map_grid->rows[y][x + 1] == ' ')
		return (1);
	if (map_grid->rows[y - 1][x] == ' ' || map_grid->rows[y + 1][x] == ' ')
		return (1);
	return (0);
}

static uint32_t	cell_color(const t_map_grid *map_grid, size_t x, size_t y)
{
	char	cell;

	cell = map_grid->rows[y][x];
	if (is_open_cell(map_grid, x, y))
		return (0xFFD166FF);
	if (cell == '1')
		return (0x3A506BFF);
	if (cell == '0')
		return (0xEAEAEAFF);
	if (cell == 'N')
		return (0xFF595EFF);
	if (cell == 'S')
		return (0x1982C4FF);
	if (cell == 'E')
		return (0x8AC926FF);
	if (cell == 'W')
		return (0x6A4C93FF);
	return (0x0F0F0FFF);
}

static void	draw_cell(mlx_image_t *img, size_t gx, size_t gy, uint32_t color)
{
	size_t	x;
	size_t	y;
	size_t	px;
	size_t	py;

	y = 0;
	while (y < CELL_SIZE)
	{
		x = 0;
		while (x < CELL_SIZE)
		{
			px = gx * CELL_SIZE + x;
			py = gy * CELL_SIZE + y;
			mlx_put_pixel(img, (uint32_t)px, (uint32_t)py, color);
			x++;
		}
		y++;
	}
}

int	run_visual_demo(const t_map_grid *map_grid)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	size_t		x;
	size_t		y;

	mlx = mlx_init((int)(map_grid->width * CELL_SIZE),
			(int)(map_grid->height * CELL_SIZE),
			"cube3d map visual", true);
	if (!mlx)
		return (0);
	img = mlx_new_image(mlx,
		(uint32_t)(map_grid->width * CELL_SIZE),
		(uint32_t)(map_grid->height * CELL_SIZE));
	if (!img || mlx_image_to_window(mlx, img, 0, 0) < 0)
		return (mlx_terminate(mlx), 0);
	y = 0;
	while (y < map_grid->height)
	{
		x = 0;
		while (x < map_grid->width)
		{
			draw_cell(img, x, y, cell_color(map_grid, x, y));
			x++;
		}
		y++;
	}
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (1);
}