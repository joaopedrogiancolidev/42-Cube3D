/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 14:22:31 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/08 00:32:22 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	print_error_prefix(void)
{
	ft_printf("Error\n");
}

void	parser_error_invalid_line(int line_no)
{
	print_error_prefix();
	ft_printf("invalid line at line %d\n", line_no);
}

void	parser_error_element_after_map(int line_no)
{
	print_error_prefix();
	ft_printf("element after map started at line %d\n", line_no);
}

void	parser_error_duplicate(const char *key, int line_no)
{
	print_error_prefix();
	ft_printf("duplicate element '%s' at line %d\n", key, line_no);
}

void	parser_error_missing(const char *key)
{
	print_error_prefix();
	ft_printf("missing required element '%s'\n", key);
}
