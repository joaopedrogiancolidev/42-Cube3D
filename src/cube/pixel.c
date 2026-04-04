/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:34:50 by arthur            #+#    #+#             */
/*   Updated: 2026/04/04 14:21:03 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a );
	// 24, 16, 8, a
}

static uint32_t	get_texel_color(mlx_texture_t *tex, uint32_t x, uint32_t y)
{
	uint8_t	*px;
	uint32_t	idx;

	idx = (y * tex->width + x) * tex->bytes_per_pixel;
	px = tex->pixels + idx;
	return (ft_pixel(px[0], px[1], px[2], px[3]));
}

void	draw_textured_column(t_cube_data *cube_data, int x)
{
	t_raycast		*r;
	mlx_texture_t	*tex;
	uint32_t		tex_w;
	uint32_t		tex_h;
	double			wall_x;
	double			step;
	double			tex_pos;
	int				y;
	int				tex_x;
	int				tex_y;
	uint32_t		color;

	r = &cube_data->raycast;
	tex = NULL;
	if (r->side == 0)
	{
		if (r->raydir_x > 0)
			tex = cube_data->tex_we;
		else
			tex = cube_data->tex_ea;
	}
	else
	{
		if (r->raydir_y > 0)
			tex = cube_data->tex_so;
		else
			tex = cube_data->tex_no;
	}
	if (!tex)
	{
		change_color(cube_data, r);
		ver_line(cube_data->image_cube.image, x, r);
		return ;
	}
	tex_w = tex->width;
	tex_h = tex->height;
	if (r->side == 0)
		wall_x = r->pos_y + r->perp_wall_dist * r->raydir_y;
	else
		wall_x = r->pos_x + r->perp_wall_dist * r->raydir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex_w);
	if (r->side == 0 && r->raydir_x > 0)
		tex_x = (int)tex_w - tex_x - 1;
	if (r->side == 1 && r->raydir_y < 0)
		tex_x = (int)tex_w - tex_x - 1;
	step = (double)tex_h / (double)r->line_height;
	// ARRUMAR POSIÇAO MATEMATICA DA TEXTURA
	// Tenho que fazer o resize com base no tamanho total.
	// CALCULO DE QUAL TEXTURA PEGAR REFERENTE AO PARSER
	tex_pos = (r->draw_start - (int)cube_data->image_cube.height / 2
			+ r->line_height / 2) * step;
	y = r->draw_start;
	while (y <= r->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= (int)tex_h)
			tex_y = (int)tex_h - 1;
		tex_pos += step;
		color = get_texel_color(tex, (uint32_t)tex_x, (uint32_t)tex_y);
		if (r->side == 1)
			color = (color >> 1) & 0x7F7F7FFF;
		if (x >= 0 && x < (int)cube_data->image_cube.width
			&& y >= 0 && y < (int)cube_data->image_cube.height)
			mlx_put_pixel(cube_data->image_cube.image, x, y, color);
		y++;
	}
}

void	ver_line(mlx_image_t	*img, int x, t_raycast *raycast)
{
	int	y;

	y = raycast->draw_start;
	while (y <= raycast->draw_end)
	{
		if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
		{
			mlx_put_pixel(img, x, y, raycast->color);
		}
		y++;
	}
}

void	refresh_pixel(void *param)
{
	t_cube_data	*cube_data;
	int			y;
	int			x;
	uint32_t	ceil_color;
	uint32_t	floor_color;

	cube_data = param;
	ceil_color = ft_pixel(cube_data->ceiling_rgb[0],
			cube_data->ceiling_rgb[1], cube_data->ceiling_rgb[2], 255);
	floor_color = ft_pixel(cube_data->floor_rgb[0],
			cube_data->floor_rgb[1], cube_data->floor_rgb[2], 255);
	y = 0;
	x = 0;
	while (y < cube_data->image_cube.height)
	{
		x = 0;
		while (x < cube_data->image_cube.width)
		{
			if (y > (int)cube_data->image_cube.height / 2)
				mlx_put_pixel(cube_data->image_cube.image, x, y, floor_color);
			else
				mlx_put_pixel(cube_data->image_cube.image, x, y, ceil_color);
			x ++;
		}
		y ++;
	}
}
