/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:06:49 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/08 00:07:50 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	has_cub_extension(const char *path)
{
	int	len;

	len = (int)ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + (len - 4), ".cub", 4) == 0);
}

int	parse_cub_file_data(const char *path, t_parser_config *cfg_out,
		t_map_grid *map_out)
{
	int	fd;
	int	has_invalid;

	if (!has_cub_extension(path))
	{
		parser_error_invalid_extension(path);
		return (1);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		parser_error_file_open(path);
		return (1);
	}
	has_invalid = load_file_lines_data(fd, path, cfg_out, map_out);
	close(fd);
	return (has_invalid);
}

int	parse_cub_file(const char *path)
{
	t_parser_config	cfg;
	t_map_grid		map;
	int				has_invalid;

	has_invalid = parse_cub_file_data(path, &cfg, &map);
	if (!has_invalid)
	{
		free_parser_config(&cfg);
		free_map_grid(&map);
	}
	return (has_invalid);
}
