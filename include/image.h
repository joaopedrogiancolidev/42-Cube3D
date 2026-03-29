/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeneze <armeneze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:26:07 by arthur            #+#    #+#             */
/*   Updated: 2026/03/29 14:19:24 by armeneze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H
# include <stdint.h>

typedef struct s_cube_data	t_cube_data;

void		init_mlx(t_cube_data *cube_data);
mlx_image_t	*create_image(mlx_t *mlx, uint32_t width, uint32_t height);
int32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int			create_image_cube(t_cube_data *cube_data);
int			create_minimap(t_cube_data *cube_data);
#endif
