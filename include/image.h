/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:26:07 by arthur            #+#    #+#             */
/*   Updated: 2026/03/19 10:19:26 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
#define IMAGE_H
# include <stdint.h>

typedef struct s_cube_data t_cube_data;

void init_mlx(t_cube_data *cube_data);
mlx_image_t *create_image(mlx_t *mlx, uint32_t width, uint32_t height);


#endif

