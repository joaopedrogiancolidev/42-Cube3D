/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 17:30:32 by arthur            #+#    #+#             */
/*   Updated: 2026/03/18 17:45:36 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_cube_data parser(int argc, char **argv)
{
	t_cube_data cube_data;
	cube_data.map = open_file_array("maps/map.cub");

	// for(int i = 0; i < 10; i++)
	// {
	// 	for(int j = 0; j < 10; j++)
	// 	{
	// 		printf("%d ", cube_data.map[i][j]);
	// 	}
	// 	printf("\n");
	// }
	
	return (cube_data);
}