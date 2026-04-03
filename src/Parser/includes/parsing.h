/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:37:35 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/03 15:38:43 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "parser_config.h"
# include "map_grid.h"

int		is_empty_line(char *line);
int		is_element_line(char *line);
int		is_map_line(char *line);
int		load_file_lines(int fd, const char *source_path);
int		load_file_lines_data(int fd, const char *source_path,
			t_parser_config *cfg_out, t_map_grid *map_out);
int		parse_cub_file(const char *path);
int		parse_cub_file_data(const char *path, t_parser_config *cfg_out,
			t_map_grid *map_out);
char	*line_type_name(char *line);

#endif