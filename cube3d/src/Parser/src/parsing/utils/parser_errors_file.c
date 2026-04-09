/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 00:20:20 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/08 00:32:01 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	print_error_prefix(void)
{
	ft_printf("Error\n");
}

void	parser_error_file_open(const char *path)
{
	print_error_prefix();
	ft_printf("could not open file: %s\n", path);
}

void	parser_error_invalid_extension(const char *path)
{
	print_error_prefix();
	ft_printf("invalid file extension (expected .cub): %s\n", path);
}
