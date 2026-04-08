/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 17:30:32 by arthur            #+#    #+#             */
/*   Updated: 2026/04/07 14:06:44 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "parser.h"

int		copy_runtime_map(t_cube_data *cube_data, t_map_grid *map_grid);
void	transfer_config_to_cube(t_cube_data *cube_data,
			t_parser_config *cfg, t_map_grid *map_grid);

int	parser(int argc, char **argv, t_cube_data *cube_data)
{
	t_parser_config	cfg;
	t_map_grid		map_grid;

	ft_memset(cube_data, 0, sizeof(*cube_data));
	if (argc != 2)
	{
		parser_error_usage();
		return (1);
	}
	if (parse_cub_file_data(argv[1], &cfg, &map_grid) != 0)
		return (1);
	transfer_config_to_cube(cube_data, &cfg, &map_grid);
	if (copy_runtime_map(cube_data, &map_grid) != 0)
	{
		free_parser_config(&cfg);
		free_map_grid(&map_grid);
		printf("Error\nmemory allocation failed for runtime map\n");
		return (1);
	}
	free_parser_config(&cfg);
	free_map_grid(&map_grid);
	return (0);
}
