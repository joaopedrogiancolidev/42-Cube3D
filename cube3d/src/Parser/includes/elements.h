/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:31:48 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/07 21:49:31 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_H
# define ELEMENTS_H

# include "parser_config.h"

int	parse_element_line(t_parser_config *cfg, char *line, int line_no);
int	validate_required_elements(t_parser_config *cfg, const char *source_path);
int	validate_texture_path(char **path_ref, const char *key,
		const char *source_path);
int	validate_rgb_value(char *raw, const char *key, int rgb[3]);

#endif