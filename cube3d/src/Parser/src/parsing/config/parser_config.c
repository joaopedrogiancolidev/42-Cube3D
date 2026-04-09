/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:35:54 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/08 00:14:26 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_parser_config(t_parser_config *cfg)
{
	cfg->no_path = NULL;
	cfg->so_path = NULL;
	cfg->we_path = NULL;
	cfg->ea_path = NULL;
	cfg->f_raw = NULL;
	cfg->c_raw = NULL;
	cfg->floor_rgb[0] = -1;
	cfg->floor_rgb[1] = -1;
	cfg->floor_rgb[2] = -1;
	cfg->ceiling_rgb[0] = -1;
	cfg->ceiling_rgb[1] = -1;
	cfg->ceiling_rgb[2] = -1;
}

void	free_parser_config(t_parser_config *cfg)
{
	free(cfg->no_path);
	free(cfg->so_path);
	free(cfg->we_path);
	free(cfg->ea_path);
	free(cfg->f_raw);
	free(cfg->c_raw);
}
