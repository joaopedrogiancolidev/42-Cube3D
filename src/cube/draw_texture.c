/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:20:00 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/08 14:59:43 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

typedef struct s_texdraw
{
	uint32_t	tex_w;
	uint32_t	tex_h;
	double		wall_x;
	double		step;
	double		tex_pos;
	int			y;
	int			tex_x;
	int			tex_y;
	uint32_t	color;
}t_texdraw;

static uint32_t	get_texel_color(mlx_texture_t *tex, uint32_t x, uint32_t y)
{
	uint8_t		*px;
	uint32_t	idx;

	idx = (y * tex->width + x) * tex->bytes_per_pixel;
	px = tex->pixels + idx;
	return (ft_pixel(px[0], px[1], px[2], px[3]));
}

static mlx_texture_t	*choose_texture(t_cube_data *cube_data,
							t_raycast *r)
{
	if (r->side == 0)
	{
		if (r->raydir_x > 0)
			return (cube_data->tex_we);
		return (cube_data->tex_ea);
	}
	if (r->raydir_y > 0)
		return (cube_data->tex_so);
	return (cube_data->tex_no);
}

static void	init_texdraw(t_texdraw *d, t_raycast *r, mlx_texture_t *tex,
				t_cube_data *cube_data)
{
	d->tex_w = tex->width;
	d->tex_h = tex->height;
	if (r->side == 0)
		d->wall_x = r->pos_y + r->perp_wall_dist * r->raydir_y;
	else
		d->wall_x = r->pos_x + r->perp_wall_dist * r->raydir_x;
	d->wall_x -= floor(d->wall_x);
	d->tex_x = (int)(d->wall_x * (double)d->tex_w);
	if (r->side == 0 && r->raydir_x > 0)
		d->tex_x = (int)d->tex_w - d->tex_x - 1;
	if (r->side == 1 && r->raydir_y < 0)
		d->tex_x = (int)d->tex_w - d->tex_x - 1;
	d->step = (double)d->tex_h / (double)r->line_height;
	d->tex_pos = (r->draw_start - (int)cube_data->image_cube.height / 2
			+ r->line_height / 2) * d->step;
	d->y = r->draw_start;
}

static void	draw_tex_loop(t_cube_data *cube_data, t_raycast *r,
				mlx_texture_t *tex, int x)
{
	t_texdraw	d;

	init_texdraw(&d, r, tex, cube_data);
	while (d.y <= r->draw_end)
	{
		d.tex_y = (int)d.tex_pos;
		if (d.tex_y < 0)
			d.tex_y = 0;
		else if (d.tex_y >= (int)d.tex_h)
			d.tex_y = (int)d.tex_h - 1;
		d.tex_pos += d.step;
		d.color = get_texel_color(tex, (uint32_t)d.tex_x,
				(uint32_t)d.tex_y);
		if (r->side == 1)
			d.color = (d.color >> 1) & 0x7F7F7FFF;
		if (x >= 0 && x < (int)cube_data->image_cube.width
			&& d.y >= 0 && d.y < (int)cube_data->image_cube.height)
			mlx_put_pixel(cube_data->image_cube.image, x, d.y, d.color);
		d.y++;
	}
}

void	draw_textured_column(t_cube_data *cube_data, int x)
{
	t_raycast		*r;
	mlx_texture_t	*tex;

	r = &cube_data->raycast;
	tex = choose_texture(cube_data, r);
	if (!tex)
	{
		change_color(cube_data, r);
		ver_line(cube_data->image_cube.image, x, r);
		return ;
	}
	draw_tex_loop(cube_data, r, tex, x);
}
