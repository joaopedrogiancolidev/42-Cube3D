/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors_config.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 00:20:10 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/08 00:32:01 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	print_error_prefix(void)
{
	ft_printf("Error\n");
}

void	parser_error_invalid_rgb(const char *key)
{
	print_error_prefix();
	ft_printf("invalid RGB value for '%s' (expected R,G,B in [0,255])\n", key);
}

void	parser_error_invalid_texture(const char *key, const char *path)
{
	print_error_prefix();
	ft_printf("invalid texture path for '%s': %s\n", key, path);
}

void	parser_error_usage(void)
{
	print_error_prefix();
	ft_printf("usage: ./maps <map.cub>\n");
}
