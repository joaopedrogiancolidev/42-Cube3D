/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 00:14:07 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/08 00:14:13 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	main(int argc, char **argv)
{
	int		has_invalid;

	if (argc != 2)
	{
		parser_error_usage();
		return (1);
	}
	has_invalid = parse_cub_file(argv[1]);
	if (has_invalid)
		return (1);
	return (0);
}
