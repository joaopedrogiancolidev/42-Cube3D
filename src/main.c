/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeneze <armeneze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:57:22 by arthur            #+#    #+#             */
/*   Updated: 2026/03/25 13:56:20 by armeneze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	main(int argc, char **argv)
{
	t_cube_data	cube_data;

	if (parser(argc, argv, &cube_data) != 0)
		return (1);
	if (start_cube(&cube_data) > 0)
	{
		printf("error\n");
		free_all(&cube_data);
		return (1);
	}
	free_all(&cube_data);
	return (0);
}
