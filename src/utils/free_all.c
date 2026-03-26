/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeneze <armeneze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:48:42 by arthur            #+#    #+#             */
/*   Updated: 2026/03/25 16:11:39 by armeneze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_all(t_cube_data *cube_data)
{
	int	i;

	if (!cube_data || !cube_data->map)
		return ;
	i = 0;
	while (i < cube_data->map_height)
	{
		free(cube_data->map[i]);
		i++;
	}
	free(cube_data->map);
	cube_data->map = NULL;
}
