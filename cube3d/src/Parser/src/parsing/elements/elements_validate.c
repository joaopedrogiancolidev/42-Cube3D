/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_validate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 20:46:48 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/07 21:49:31 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	print_missing_if_null(char *value, const char *key)
{
	if (!value)
	{
		parser_error_missing(key);
		return (1);
	}
	return (0);
}

int	validate_required_elements(t_parser_config *cfg, const char *source_path)
{
	int	has_error;

	has_error = 0;
	has_error |= print_missing_if_null(cfg->no_path, "NO");
	has_error |= print_missing_if_null(cfg->so_path, "SO");
	has_error |= print_missing_if_null(cfg->we_path, "WE");
	has_error |= print_missing_if_null(cfg->ea_path, "EA");
	has_error |= print_missing_if_null(cfg->f_raw, "F");
	has_error |= print_missing_if_null(cfg->c_raw, "C");
	if (!has_error)
	{
		has_error |= validate_texture_path(&cfg->no_path, "NO", source_path);
		has_error |= validate_texture_path(&cfg->so_path, "SO", source_path);
		has_error |= validate_texture_path(&cfg->we_path, "WE", source_path);
		has_error |= validate_texture_path(&cfg->ea_path, "EA", source_path);
	}
	if (!has_error)
	{
		has_error |= validate_rgb_value(cfg->f_raw, "F", cfg->floor_rgb);
		has_error |= validate_rgb_value(cfg->c_raw, "C", cfg->ceiling_rgb);
	}
	return (has_error);
}
